#pragma once

#include "byte_buffer.hpp"
#include "component/console/console.hpp"

#include <utils/flags.hpp>
#include <utils/io.hpp>
#include <utils/string.hpp>

namespace demonware::request_trace
{
	// Logs the request payload of a Demonware task that is not emulated yet so
	// the wire format can be studied. The first bytes go to the console; with
	// -demonware_debug the complete payload is written to s2x/dump/dw/ so that
	// large requests never have to pass through the console formatter.
	inline void log(const char* service, const char* task, byte_buffer* buffer)
	{
		constexpr std::size_t preview_size = 48;

		const auto payload = buffer ? buffer->get_remaining() : std::string{};
		const auto preview = utils::string::dump_hex(payload.substr(0, preview_size));

		console::info("[DW-trace] %s::%s request: %zu bytes%s%s\n", service, task, payload.size(),
			preview.empty() ? "" : " | ", preview.data());

		static const auto dump_payloads = utils::flags::has_flag("-demonware_debug");
		if (!dump_payloads || payload.empty())
		{
			return;
		}

		static std::atomic_uint32_t sequence{};
		const auto path = utils::string::va("s2x/dump/dw/%s_%s_%03u.bin", service, task, sequence++);
		if (utils::io::write_file(path, payload))
		{
			console::info("[DW-trace] wrote %s\n", path);
		}
	}
}
