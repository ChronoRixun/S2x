#pragma once

#include "byte_buffer.hpp"
#include "component/console/console.hpp"
#include <utils/io.hpp>

namespace demonware::hq_protocol
{
	inline bool padding(byte_buffer* buffer)
	{
		const auto tail = buffer->get_remaining();
		return tail.size() <= 15 && std::all_of(tail.begin(), tail.end(), [](char value) { return value == 0; });
	}

	inline void trace(const char* label, const std::string& bytes)
	{
		static std::atomic_uint64_t sequence{};
		const auto path = std::string{"s2x/dump/dw/hq_"} + label + "_" +
			std::to_string(GetCurrentProcessId()) + "_" + std::to_string(sequence++) + ".bin";
		if (!utils::io::write_file(path, bytes)) console::error("[HQ protocol] cannot write %s\n", path.c_str());
		console::info("[HQ protocol] %s: %zu raw bytes at %s\n", label, bytes.size(), path.c_str());
	}
}
