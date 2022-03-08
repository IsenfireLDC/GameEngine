/*
 * units.hpp
 *
 * Define units for use throughout the engine
 */

#ifndef _UNITS_HPP_
#define _UNITS_HPP_

#include <chrono>

namespace Engine {
	using Clock = std::chrono::system_clock;
};

namespace Engine::Units {
	using Time = std::chrono::nanoseconds;
	using TimePoint = Engine::Clock::time_point;
};

#endif
