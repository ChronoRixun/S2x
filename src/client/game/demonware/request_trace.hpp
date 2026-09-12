#pragma once

#include "byte_buffer.hpp"
#include "component/console/console.hpp"

#include <utils/string.hpp>

namespace demonware::request_trace
{
	// Logs the request payload of a Demonware task that is not emulated yet so
	// the wire format can be studied from the console log. The first bytes go
	// to the regular console; the full payload only with -demonware_debug.
	inline void log(const char* service, const char* task, byte_buffer* buffer)
	{
		constexpr std::size_t preview_size = 48;

		const auto payload = buffer ? buffer->get_remaining() : std::string{};
		const auto preview = utils::string::dump_hex(payload.substr(0, preview_size));

		console::info("[DW-trace] %s::%s request: %zu bytes%s%s\n", service, task, payload.size(),
			preview.empty() ? "" : " | ", preview.data());

		if (payload.size() > preview_size)
		{
			console::demonware("[DW-trace] %s::%s payload: %s\n", service, task,
				utils::string::dump_hex(payload).data());
		}
	}
}
