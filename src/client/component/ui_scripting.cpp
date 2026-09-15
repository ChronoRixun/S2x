#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "scheduler.hpp"
#include "command.hpp"
#include "console/console.hpp"

#include "game/game.hpp"
#include "game/dvars.hpp"
#include "game/ui_scripting/execution.hpp"

#include "filesystem.hpp"
#include "ui_scripting.hpp"

#include <utils/hook.hpp>
#include <utils/io.hpp>
#include <utils/finally.hpp>
#include <utils/string.hpp>

namespace ui_scripting
{
	namespace
	{
		std::unordered_map<game::hks::cclosure*, std::function<arguments(const function_arguments& args)>> converted_functions;
		std::vector<std::function<void()>> start_callbacks;

		utils::hook::detour hks_start_hook;
		utils::hook::detour hks_shutdown_hook;
		utils::hook::detour hks_package_require_hook;

		struct script
		{
			std::string name;
			std::string root;
		};

		struct globals_s
		{
			std::string in_require_script;
			std::vector<script> loaded_scripts;
			bool load_raw_script{};
			std::string raw_script_name{};
			std::vector<std::string> script_stack{};
		};

		std::unordered_map<game::hks::lua_State*, globals_s> state_globals{};
		thread_local game::hks::lua_State* active_lua_state{};
		thread_local globals_s* active_lua_globals{};

		std::string normalize_script_path(std::string path)
		{
			if (!path.empty() && path[0] == '@')
			{
				path.erase(path.begin());
			}

			std::ranges::replace(path, '\\', '/');
			return path;
		}

		globals_s& get_globals(game::hks::lua_State* state)
		{
			return state_globals[state];
		}

		globals_s& get_active_globals(game::hks::lua_State* state)
		{
			if (active_lua_state == state && active_lua_globals)
			{
				return *active_lua_globals;
			}

			return get_globals(state);
		}

		bool is_loaded_script(const globals_s& globals, const std::string& name)
		{
			const auto normalized_name = normalize_script_path(name);
			return std::ranges::any_of(globals.loaded_scripts, [&normalized_name](const auto& loaded_script)
			{
				return loaded_script.name == normalized_name;
			});
		}

		std::string select_require_script(const globals_s& globals, const std::string& hks_script)
		{
			if (is_loaded_script(globals, hks_script))
			{
				return hks_script;
			}

			if (!globals.script_stack.empty())
			{
				return globals.script_stack.back();
			}

			return hks_script;
		}

		std::string get_root_script(globals_s& globals, const std::string& name)
		{
			const auto normalized_name = normalize_script_path(name);
			for (const auto& loaded_script : globals.loaded_scripts)
			{
				if (loaded_script.name == normalized_name)
				{
					return loaded_script.root;
				}
			}

			if (normalized_name.find("ui_scripts/") != std::string::npos && utils::io::file_exists(normalized_name))
			{
				globals.loaded_scripts.push_back({normalized_name, normalized_name});
				return normalized_name;
			}

			return {};
		}

		std::string find_local_script(const std::string& folder, const std::string& name)
		{
			std::vector<std::string> candidates{};

			const auto add_candidate = [&](std::string path)
			{
				path = normalize_script_path(std::move(path));
				if (!path.ends_with(".lua"))
				{
					path += ".lua";
				}

				if (std::ranges::find(candidates, path) == candidates.end())
				{
					candidates.push_back(std::move(path));
				}
			};

			add_candidate(folder + "/" + name);

			auto module_name = name;
			const auto has_lua_extension = module_name.ends_with(".lua");
			if (has_lua_extension)
			{
				module_name.resize(module_name.size() - 4);
			}

			std::ranges::replace(module_name, '.', '/');
			if (has_lua_extension)
			{
				module_name += ".lua";
			}

			add_candidate(folder + "/" + module_name);

			if (const auto slash = module_name.find('/'); slash != std::string::npos)
			{
				add_candidate(folder + "/" + module_name.substr(slash + 1));
			}

			if (const auto slash = module_name.find_last_of('/'); slash != std::string::npos)
			{
				add_candidate(folder + "/" + module_name.substr(slash + 1));
			}

			for (const auto& candidate : candidates)
			{
				if (utils::io::file_exists(candidate))
				{
					return candidate;
				}
			}

			return {};
		}

		table get_globals()
		{
			const auto state = *game::hks::lui_lua_state;
			return state->globals.v.table;
		}

		void print_error(const std::string& error)
		{
			console::error("************** LUI script execution error **************\n");
			console::error("%s\n", error.data());
			console::error("********************************************************\n");
		}

		void print_loading_script(const std::string& name)
		{
			console::info("Loading LUI script '%s'\n", name.data());
		}

		std::string get_current_script(game::hks::lua_State* state)
		{
			game::hks::lua_Debug info{};
			game::hks::hksi_lua_getstack(state, 1, &info);
			game::hks::hksi_lua_getinfo(state, "nSl", &info);
			return info.short_src;
		}

		int load_buffer(game::hks::lua_State* state, const std::string& name, const std::string& data)
		{
			const auto sharing_mode = state->m_global->m_bytecodeSharingMode;
			state->m_global->m_bytecodeSharingMode = game::hks::HKS_BYTECODE_SHARING_ON;
			const auto _0 = utils::finally([&]()
			{
				state->m_global->m_bytecodeSharingMode = sharing_mode;
			});

			game::hks::HksCompilerSettings compiler_settings{};
			return game::hks::hksi_hksL_loadbuffer(state, &compiler_settings, data.data(), static_cast<unsigned int>(data.size()), name.data());
		}

		std::string get_load_error(game::hks::lua_State* state, const game::hks::HksObject* top, const int result)
		{
			if (state->m_apistack.top > top)
			{
				const auto& error = state->m_apistack.top[-1];
				if (error.t == game::hks::TSTRING && error.v.str)
				{
					return error.v.str->m_data;
				}
			}

			return utils::string::va("compiler returned %d", result);
		}

		void load_script(const std::string& name, const std::string& data)
		{
			const auto state = *game::hks::lui_lua_state;
			auto& globals = get_globals(state);

			const auto normalized_name = normalize_script_path(name);

			const auto previous_active_state = active_lua_state;
			const auto previous_active_globals = active_lua_globals;
			const auto previous_require_script = globals.in_require_script;

			active_lua_state = state;
			active_lua_globals = &globals;
			globals.in_require_script = normalized_name;

			globals.loaded_scripts.push_back({ normalized_name, normalized_name });
			globals.script_stack.push_back(normalized_name);

			const auto restore_state = [&]()
			{
				if (!globals.script_stack.empty() && globals.script_stack.back() == normalized_name)
				{
					globals.script_stack.pop_back();
				}

				globals.in_require_script = previous_require_script;
				active_lua_state = previous_active_state;
				active_lua_globals = previous_active_globals;
			};

			const auto lua = get_globals();

			const auto top = state->m_apistack.top;
			const auto load_result = load_buffer(state, normalized_name, data);

			const auto loaded = state->m_apistack.top > top
				? script_value(state->m_apistack.top[-1])
				: script_value();

			state->m_apistack.top = top;

			if (load_result != 0)
			{
				if (loaded.is<std::string>())
				{
					print_error(loaded.as<std::string>());
				}
				else
				{
					print_error(utils::string::va("Failed to load '%s' (%d)", normalized_name.data(), load_result));
				}

				restore_state();
				return;
			}

			if (!loaded.is<function>())
			{
				print_error(utils::string::va("Failed to load '%s': compiled chunk is not a function", normalized_name.data()));

				restore_state();
				return;
			}

			const auto results = lua["pcall"](loaded);
			if (!results[0].as<bool>())
			{
				print_error(results[1].as<std::string>());
			}

			restore_state();
		}

		bool load_scripts(const std::string& script_dir)
		{
			if (!utils::io::directory_exists(script_dir))
			{
				return false;
			}

			const auto scripts = utils::io::list_files(script_dir);

			for (const auto& script : scripts)
			{
				std::string data{};
				if (std::filesystem::is_directory(script) && utils::io::read_file(script / "__init__.lua", &data))
				{
					print_loading_script(script.generic_string());
					load_script((script / "__init__.lua").generic_string(), data);
				}
			}

			return true;
		}

		void setup_functions()
		{
			const auto lua = get_globals();

			using game = table;
			auto game_type = game();
			lua["game"] = game_type;

			game_type["issingleplayer"] = [](const game&)
			{
				return ::game::environment::is_singleplayer();
			};

			game_type["ismultiplayer"] = [](const game&)
			{
				return ::game::environment::is_multiplayer();
			};
		}

		void run_start_callbacks()
		{
			for (const auto& callback : start_callbacks)
			{
				try
				{
					callback();
				}
				catch (const std::exception& e)
				{
					console::error("Failed to run LUI start callback: %s\n", e.what());
				}
			}
		}

		void enable_globals()
		{
			const auto lua = get_globals();
			const std::string script =
				"local g = getmetatable(_G)\n"
				"if not g then\n"
					"g = {}\n"
					"setmetatable(_G, g)\n"
				"end\n"
				"g.__newindex = nil\n";

			(void)lua["loadstring"](script)[0]();
		}

		void start()
		{
			get_globals(*game::hks::lui_lua_state) = {};
			const auto lua = get_globals();

			enable_globals();
			setup_functions();

			lua["print"] = function(reinterpret_cast<game::hks::lua_function>(game::hks::base_print.get()));
			lua["table"]["unpack"] = lua["unpack"];
			lua["luiglobals"] = lua;

			const auto search_paths = filesystem::get_search_paths_rev();
			auto script_directories = 0u;

			for (const auto& path : search_paths)
			{
				const auto base = std::filesystem::path(path) / "ui_scripts";
				const auto game_dir = game::environment::uses_multiplayer_binary() ? "mp" : "sp";

				if (load_scripts(base.generic_string()))
				{
					++script_directories;
				}

				if (load_scripts((base / game_dir).generic_string()))
				{
					++script_directories;
				}
			}

			if (script_directories == 0)
			{
				// Once per process: LUI restarts (lui_restart, mode switches) rerun
				// this scan, and the directory being absent is the same fact each time.
				static std::once_flag missing_notice{};
				std::call_once(missing_notice, [&]
				{
					console::info("[LUI] No ui_scripts directory was found in %zu loose file search path(s); custom UI scripts are not loaded.\n",
						search_paths.size());
				});
			}

			run_start_callbacks();
		}

		void try_start()
		{
			try
			{
				start();
			}
			catch (const std::exception& e)
			{
				console::error("Failed to load LUI scripts: %s\n", e.what());
			}
		}

		void hks_start_stub(const bool frontend, const bool cg)
		{
			const auto _0 = utils::finally(&try_start);
			hks_start_hook.invoke<void>(frontend, cg);
		}

		void hks_shutdown_stub()
		{
			converted_functions.clear();
			state_globals.clear();
			return hks_shutdown_hook.invoke<void>();
		}

		int hks_package_require_stub(game::hks::lua_State* state)
		{
			auto& globals = get_active_globals(state);

			const auto hks_script = normalize_script_path(get_current_script(state));
			const auto script = select_require_script(globals, hks_script);
			const auto root = get_root_script(globals, script);

			const auto previous_active_state = active_lua_state;
			const auto previous_active_globals = active_lua_globals;
			const auto previous_require_script = globals.in_require_script;

			active_lua_state = state;
			active_lua_globals = &globals;
			globals.in_require_script = root;

			const auto result = hks_package_require_hook.invoke<int>(state);

			globals.in_require_script = previous_require_script;
			active_lua_state = previous_active_state;
			active_lua_globals = previous_active_globals;

			return result;
		}

		game::XAssetHeader db_find_x_asset_header_stub(game::XAssetType type, const char* name, int allow_create_default)
		{
			game::XAssetHeader header{ .luaFile = nullptr };

			if (!active_lua_state || !name)
			{
				return game::DB_FindXAssetHeader(type, name, allow_create_default);
			}

			if (type != game::ASSET_TYPE_LUAFILE)
			{
				return game::DB_FindXAssetHeader(type, name, allow_create_default);
			}

			auto& globals = get_active_globals(active_lua_state);

			const auto require_script = normalize_script_path(globals.in_require_script);
			if (require_script.empty() || !is_loaded_script(globals, require_script))
			{
				return game::DB_FindXAssetHeader(type, name, allow_create_default);
			}

			const auto folder_end = require_script.find_last_of('/');
			if (folder_end == std::string::npos)
			{
				return game::DB_FindXAssetHeader(type, name, allow_create_default);
			}

			const auto folder = require_script.substr(0, folder_end);
			const auto name_ = normalize_script_path(name);
			const auto target_script = find_local_script(folder, name_);

			if (!target_script.empty())
			{
				globals.load_raw_script = true;
				globals.raw_script_name = target_script;
				header.luaFile = reinterpret_cast<game::LuaFile*>(1);
				return header;
			}

			return game::DB_FindXAssetHeader(type, name, allow_create_default);
		}

		int hks_load_stub(game::hks::lua_State* state, void* compiler_options,
			void* reader, void* reader_data, const char* chunk_name)
		{
			auto& globals = get_active_globals(state);

			const auto previous_active_state = active_lua_state;
			const auto previous_active_globals = active_lua_globals;

			active_lua_state = state;
			active_lua_globals = &globals;

			if (globals.load_raw_script)
			{
				globals.load_raw_script = false;

				const auto script_name = globals.raw_script_name;
				const auto require_root = globals.in_require_script;

				const auto top = state->m_apistack.top;
				const auto result = load_buffer(state, script_name, utils::io::read_file(script_name));

				if (result != 0)
				{
					const auto error = get_load_error(state, top, result);

					state->m_apistack.top = top;

					print_error(utils::string::va(
						"Failed to load custom Lua script '%s': %s",
						script_name.data(),
						error.data()
					));

					active_lua_state = previous_active_state;
					active_lua_globals = previous_active_globals;

					return result;
				}

				globals.loaded_scripts.push_back({ script_name, require_root });

				active_lua_state = previous_active_state;
				active_lua_globals = previous_active_globals;

				return result;
			}

			const auto result = game::hks::load(state, compiler_options, reader, reader_data, chunk_name);

			active_lua_state = previous_active_state;
			active_lua_globals = previous_active_globals;

			return result;
		}

		int main_handler(game::hks::lua_State* state)
		{
			const auto value = state->m_apistack.base[-1];
			if (value.t != game::hks::TCFUNCTION)
			{
				return 0;
			}

			const auto closure = value.v.cClosure;
			if (!converted_functions.contains(closure))
			{
				return 0;
			}

			const auto& function = converted_functions[closure];

			try
			{
				const auto args = get_return_values();
				const auto results = function(args);

				for (const auto& result : results)
				{
					push_value(result);
				}

				return static_cast<int>(results.size());
			}
			catch (const std::exception& e)
			{
				game::hks::hksi_luaL_error(state, e.what());
			}

			return 0;
		}

		int hks_base_printf_stub(const char* fmt, ...)
		{
			char buffer[4096]{};

			va_list args;
			va_start(args, fmt);
			const auto len = vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, fmt, args);
			va_end(args);

			if (len > 0)
			{
				console::info("[LUI] %s\n", buffer);
			}

			return len;
		}
	}

	table get_globals()
	{
		const auto state = *game::hks::lui_lua_state;
		return state->globals.v.table;
	}

	game::hks::cclosure* convert_function(const std::function<arguments(const function_arguments&)>& f)
	{
		const auto closure = game::hks::cclosure_Create(main_handler);
		converted_functions[closure] = f;
		return closure;
	}

	void on_start(const std::function<void()>& callback)
	{
		start_callbacks.push_back(callback);
	}

	namespace
	{
		const char* get_lui_type_name(const game::hks::HksObjectType type)
		{
			const auto index = static_cast<int>(type) + 2;
			if (index < 0 || index >= static_cast<int>(game::hks::NUM_TYPE_OBJECTS) + 2)
			{
				return "<invalid>";
			}

			return game::hks::s_compilerTypeName[index];
		}

		std::string describe_lui_key(const game::hks::HksObject& key)
		{
			switch (key.t)
			{
			case game::hks::TSTRING:
				return key.v.str ? key.v.str->m_data : "<string>";
			case game::hks::TNUMBER:
				return utils::string::va("%g", static_cast<double>(key.v.number));
			default:
				return utils::string::va("<%s>", get_lui_type_name(key.t));
			}
		}

		std::string describe_lui_value(const game::hks::HksObject& value)
		{
			const auto* type_name = get_lui_type_name(value.t);

			if (value.t == game::hks::TCFUNCTION && value.v.cClosure)
			{
				const auto* closure = value.v.cClosure;
				const auto* name = closure->m_name ? closure->m_name->m_data : "";
				const auto address = reinterpret_cast<std::size_t>(closure->m_function);
				const auto base = game::get_base();
				const auto* dos_header = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
				const auto* nt_headers = reinterpret_cast<const IMAGE_NT_HEADERS*>(base + dos_header->e_lfanew);
				const std::size_t image_size = nt_headers->OptionalHeader.SizeOfImage;

				// Only an address inside the game image is an engine offset that
				// dumpcode can use; S2x's own bindings and anything else are printed
				// as absolute addresses and said to be outside the image.
				if (address >= base && address - base < image_size)
				{
					return utils::string::va("%s %s @ 0x%zX", type_name, name, address - base);
				}

				return utils::string::va("%s %s @ %p (outside the game image)", type_name, name, closure->m_function);
			}

			return type_name;
		}

		// luidump <table[.subtable]> [filter] [output file]
		// Lists the entries of a LUI global table. C functions are printed
		// with their engine-relative address so stock bindings can be located.
		void dump_lui_table(const command::params& params)
		{
			if (params.size() < 2)
			{
				console::info("Usage: luidump <table[.subtable]> [filter] [output file]\n");
				console::info("Example: luidump Engine Dvar, luidump Lobby S2x lobby-functions\n");
				return;
			}

			if (!*game::hks::lui_lua_state)
			{
				console::error("luidump: LUI is not running\n");
				return;
			}

			const std::string table_path = params[1];
			const auto filter = params.size() > 2 ? utils::string::to_lower(params[2]) : std::string{};
			std::vector<std::pair<std::string, std::string>> entries{};
			auto found = false;

			game::LUI_EnterCriticalSection();

			try
			{
				script_value current = get_globals();
				for (const auto& segment : utils::string::split(table_path, '.'))
				{
					if (!current.is<table>())
					{
						break;
					}

					current = current.as<table>().get(segment);
				}

				found = current.is<table>();
				if (found)
				{
					const auto* hash_table = current.as<table>().ptr;

					if (hash_table->m_hashPart)
					{
						for (auto index = 0u; index <= hash_table->m_mask; ++index)
						{
							const auto& node = hash_table->m_hashPart[index];
							if (node.m_key.t == game::hks::TNIL || node.m_value.t == game::hks::TNIL)
							{
								continue;
							}

							entries.emplace_back(describe_lui_key(node.m_key), describe_lui_value(node.m_value));
						}
					}

					for (auto index = 0u; index < hash_table->m_arraySize; ++index)
					{
						const auto& value = hash_table->m_arrayPart[index];
						if (value.t == game::hks::TNIL)
						{
							continue;
						}

						entries.emplace_back(utils::string::va("[%u]", index + 1), describe_lui_value(value));
					}
				}
			}
			catch (const std::exception& e)
			{
				console::error("luidump: %s\n", e.what());
			}

			game::LUI_LeaveCriticalSection();

			if (!found)
			{
				console::error("luidump: '%s' is not a LUI table\n", table_path.data());
				return;
			}

			std::ranges::sort(entries);

			std::string output{};
			auto count = 0u;
			for (const auto& [key, description] : entries)
			{
				if (!filter.empty() && utils::string::to_lower(key).find(filter) == std::string::npos)
				{
					continue;
				}

				output += utils::string::va("%-48s %s\r\n", key.data(), description.data());
				++count;
			}

			if (params.size() > 3)
			{
				std::string filename = "s2x/";
				filename.append(params[3]);
				if (!filename.ends_with(".txt"))
				{
					filename.append(".txt");
				}

				if (!utils::io::write_file(filename, output))
				{
					console::error("luidump: failed to write '%s'\n", filename.data());
					return;
				}

				console::info("luidump: wrote %u entries of '%s' to '%s'\n", count, table_path.data(), filename.data());
				return;
			}

			console::info("luidump: '%s' has %u matching entr%s\n", table_path.data(), count, count == 1 ? "y" : "ies");
			for (auto line : utils::string::split(output, '\n'))
			{
				if (!line.empty() && line.back() == '\r')
				{
					line.pop_back();
				}

				if (!line.empty())
				{
					console::info("%s\n", line.data());
				}
			}
		}
	}

	class component final : public generic_component
	{
	public:

		void post_unpack() override
		{
			if (game::environment::is_dedicated())
			{
				return;
			}
			
			utils::hook::call(game::select(0x309B7B, 0x17E16B), db_find_x_asset_header_stub);
			utils::hook::call(game::select(0x309CBC, 0x17E2AC), db_find_x_asset_header_stub);
			utils::hook::call(game::select(0x309CFF, 0x17E2EF), hks_load_stub);
			utils::hook::call(game::select(0x2BA4B7, 0x12E877), hks_base_printf_stub);

			hks_package_require_hook.create(game::hks::package_require, hks_package_require_stub);
			hks_start_hook.create(game::LUI_CoD_Init, hks_start_stub);
			hks_shutdown_hook.create(game::LUI_CoD_Shutdown, hks_shutdown_stub);

			command::add("lui_restart", []()
			{
				game::LUI_CoD_Restart(true);
			});

			command::add("luidump", dump_lui_table);

			// TODO: Patch unsafe LUA functions
		}
	};
}

REGISTER_COMPONENT(ui_scripting::component)
