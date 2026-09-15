#pragma once

#include <source_location>

namespace scheduler
{
	enum pipeline
	{
		// Asynchronuous pipeline, disconnected from the game
		async = 0,

		// The game's rendering pipeline
		renderer,

		// The game's server thread
		server,

		// The game's main thread
		main,

		count,
	};

	static const bool cond_continue = false;
	static const bool cond_end = true;

	void schedule(const std::function<bool()>& callback, pipeline type = pipeline::async,
	              std::chrono::milliseconds delay = 0ms,
	              std::source_location location = std::source_location::current());
	void loop(const std::function<void()>& callback, pipeline type = pipeline::async,
	          std::chrono::milliseconds delay = 0ms,
	          std::source_location location = std::source_location::current());
	void once(const std::function<void()>& callback, pipeline type = pipeline::async,
	          std::chrono::milliseconds delay = 0ms,
	          std::source_location location = std::source_location::current());
	void on_game_initialized(const std::function<void()>& callback, pipeline type = pipeline::async,
	                         std::chrono::milliseconds delay = 0ms);
}
