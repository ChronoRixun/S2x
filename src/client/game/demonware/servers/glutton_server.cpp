#include <std_include.hpp>
#include "../dw_include.hpp"

#include "glutton_server.hpp"

#include "../achievement_response.hpp"
#include "../achievement_store.hpp"

#include "component/console/console.hpp"

#include "steam/steam.hpp"
#include <utils/flags.hpp>
#include <utils/io.hpp>
#include <utils/string.hpp>
#include <atomic>
#include <cctype>
#include <mutex>
#include <set>
#include <string_view>

namespace demonware
{
	namespace
	{
		// One bounded line per unhandled Achievement Engine action per session. The
		// action name comes off the wire, so it is cut and escaped; the body can
		// carry user identifiers, so it only goes to a dump file with
		// -demonware_debug, never to the console log.
		void log_unhandled_action(const std::string_view action, const std::string& body)
		{
			static std::mutex mutex{};
			static std::set<std::string> seen{};
			static std::atomic_uint32_t sequence{};
			constexpr std::size_t maximum_seen = 64;
			constexpr std::size_t maximum_name = 64;
			constexpr std::uint32_t maximum_dumps = 512;

			std::string name{action.substr(0, maximum_name)};
			for (auto& character : name)
			{
				if (static_cast<unsigned char>(character) < 0x20 || character == 0x7F)
				{
					character = '?';
				}
			}

			{
				std::lock_guard lock{mutex};
				if (seen.size() < maximum_seen && seen.insert(name).second)
				{
					console::info("[DW]: [glutton]: unhandled action '%s' (%zu bytes; first this session)\n",
						name.data(), body.size());
				}
			}

			static const auto dump_payloads = utils::flags::has_flag("-demonware_debug");
			if (!dump_payloads || body.empty())
			{
				return;
			}

			const auto index = sequence++;
			if (index >= maximum_dumps)
			{
				return;
			}

			auto file_name = name;
			for (auto& character : file_name)
			{
				if (!std::isalnum(static_cast<unsigned char>(character)))
				{
					character = '_';
				}
			}

			const auto path = utils::string::va("s2x/dump/dw/glutton_%s_%03u.bin", file_name.data(), index);
			if (utils::io::write_file(path, body))
			{
				console::info("[DW-trace] wrote %s\n", path);
			}
		}
	}
}

namespace demonware
{
	namespace
	{
		void add_user_achievements(rapidjson::Value& users, const std::string_view user_id,
			const std::vector<achievement_record>& achievements,
			rapidjson::Document::AllocatorType& allocator)
		{
			rapidjson::Value key{user_id.data(),
				static_cast<rapidjson::SizeType>(user_id.size()), allocator};
			auto array = achievement_response::serialize_achievements(achievements, allocator);
			users.AddMember(key, array, allocator);
		}
	}

	void glutton_server::handle_request(const http_request& http_request)
	{
		if (http_request.target.find("/secureingest/") != std::string::npos)
		{
			rapidjson::Document response{};
			response.SetObject();
			send_json(response);
			return;
		}

		rapidjson::Document request{};
		request.Parse(http_request.body.data(), http_request.body.size());
		if (request.HasParseError() || !request.IsObject())
		{
			console::error("[DW]: [glutton]: received an invalid request.\n");
			return;
		}

		const auto* action = request.HasMember("Action") && request["Action"].IsString()
			? request["Action"].GetString()
			: "";

		rapidjson::Document response{};
		response.SetObject();
		auto& allocator = response.GetAllocator();
		response.AddMember("Version", 0, allocator);
		response.AddMember("Action", rapidjson::Value{action,
			static_cast<rapidjson::SizeType>(std::strlen(action)), allocator}, allocator);
		response.AddMember("Status", "ok", allocator);

		if (request.HasMember("ClientTx") && request["ClientTx"].IsString())
		{
			const auto& client_tx = request["ClientTx"];
			response.AddMember("ClientTx", rapidjson::Value{client_tx.GetString(),
				client_tx.GetStringLength(), allocator}, allocator);
		}

		const auto is_single_user_request = std::strcmp(action, "get_user_achievements") == 0;
		const auto is_multi_user_request =
			std::strcmp(action, "get_user_achievements_for_users") == 0;
		if (is_single_user_request || is_multi_user_request)
		{
			const auto achievements = achievement_store::get_all();
			if (is_multi_user_request)
			{
				rapidjson::Value users{rapidjson::kObjectType};
				bool added_user{};
				if (request.HasMember("UserIDs") && request["UserIDs"].IsArray())
				{
					for (const auto& user : request["UserIDs"].GetArray())
					{
						if (user.IsString())
						{
							add_user_achievements(users,
								{user.GetString(), user.GetStringLength()}, achievements, allocator);
							added_user = true;
						}
						else if (user.IsUint64())
						{
							const auto user_id = std::to_string(user.GetUint64());
							add_user_achievements(users, user_id, achievements, allocator);
							added_user = true;
						}
					}
				}

				if (!added_user)
				{
					const auto user_id = std::to_string(steam::SteamUser()->GetSteamID().bits);
					add_user_achievements(users, user_id, achievements, allocator);
				}

				response.AddMember("Achievements", users, allocator);
			}
			else
			{
				auto array = achievement_response::serialize_achievements(achievements, allocator);
				response.AddMember("Achievements", array, allocator);
			}

			response.AddMember("NextPageToken", "", allocator);
			console::demonware("[DW]: [glutton]: returned %zu user achievements.\n",
				achievements.size());
		}
		else
		{
			// Unhandled Achievement Engine actions are answered with an empty success
			// reply; log them so progression reports that vanish here can be found.
			log_unhandled_action(action, http_request.body);
		}

		send_json(response);
	}
}
