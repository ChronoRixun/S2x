#pragma once

#include "byte_buffer.hpp"
#include "component/console/console.hpp"

#include <utils/flags.hpp>
#include <utils/io.hpp>
#include <utils/string.hpp>

#include <atomic>
#include <mutex>
#include <set>
#include <string>

namespace demonware::request_trace
{
	// Notes a Demonware task request that is not emulated, or only stubbed, so
	// the wire format can be studied. The ordinary log gets one bounded line per
	// service and task per session, carrying the byte count only: request
	// payloads can hold user identifiers and never belong in the console log.
	// With -demonware_debug the complete payload is written to s2x/dump/dw/, up
	// to a per-session cap of files.
	inline void log(const char* service, const char* task, byte_buffer* buffer)
	{
		static std::mutex mutex{};
		static std::set<std::string> seen{};
		static std::atomic_uint32_t sequence{};
		constexpr std::size_t maximum_seen = 256;
		constexpr std::uint32_t maximum_dumps = 512;

		const auto remaining = buffer ? buffer->remaining() : std::size_t{};

		{
			std::lock_guard lock{mutex};
			if (seen.size() < maximum_seen && seen.insert(std::string{service} + "::" + task).second)
			{
				console::info("[DW-trace] %s::%s request: %zu bytes (first this session; later ones are not logged)\n",
					service, task, remaining);
			}
		}

		static const auto dump_payloads = utils::flags::has_flag("-demonware_debug");
		if (!dump_payloads || !buffer || remaining == 0)
		{
			return;
		}

		const auto index = sequence++;
		if (index >= maximum_dumps)
		{
			if (index == maximum_dumps)
			{
				console::warn("[DW-trace] %u payload files written this session; further payloads are not dumped\n",
					maximum_dumps);
			}

			return;
		}

		const auto payload = buffer->get_remaining();
		const auto path = utils::string::va("s2x/dump/dw/%s_%s_%03u.bin", service, task, index);
		if (utils::io::write_file(path, payload))
		{
			console::info("[DW-trace] wrote %s\n", path);
		}
	}
}
