#include <std_include.hpp>
#include <chrono>
using namespace std::chrono_literals;
#include "component/scheduler.hpp"
#include "component/console/console.hpp"
#include <utils/concurrency.hpp>
#include <cassert>

// The runner extracts the unchanged production pipeline and submission functions,
// excluding native hooks and component startup, into this generated include.
#include "scheduler-under-test.inc"

int main()
{
	unsigned once_calls{}, loop_calls{}, unknown_calls{}, healthy_calls{};
	scheduler::once([&] { ++once_calls; throw std::runtime_error("once failure"); });
	scheduler::loop([&] { ++loop_calls; throw std::runtime_error("loop failure"); });
	scheduler::once([&] { ++unknown_calls; throw 7; });
	scheduler::loop([&] { ++healthy_calls; });
	for (unsigned i = 0; i < 5; ++i) scheduler::pipelines[scheduler::async].execute();
	assert(once_calls == 1 && loop_calls == 1 && unknown_calls == 1 && healthy_calls == 5);
	assert(console::errors.size() == 3);
	for (const auto& error : console::errors)
		assert(error.find("dropped task") != std::string::npos && error.find("main") != std::string::npos &&
			error.find("scheduler-round1-tests.cpp") != std::string::npos);
	std::cout << "PASS: scheduler drops throwing once/loop/unknown tasks, one named error each, healthy loop continues\n";
}
