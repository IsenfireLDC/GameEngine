/*
 * THIS FILE SHOULD BE INCLUDED AFTER STL HEADERS
 * This may be included in header files
 *
 * Contains type definitions for the engine
 */

namespace Engine {

/*
 * <chrono>
 *
 * C++ stl chrono
 * Types for timing
 *
 * FPS conversion function template
 */
#ifdef _GLIBCXX_CHRONO
#ifndef _ENGINE_TIME
#define _ENGINE_TIME
	using Clock = std::chrono::system_clock;

	namespace Units {
		using Time = std::chrono::nanoseconds;
		using TimePoint = Engine::Clock::time_point;
	};


	template<class duration = Units::Time>
	duration FPS(int fps) {
		intmax_t ticks = duration::period::den / (fps * duration::period::num);
		return duration(ticks);
	};
#endif
#endif

};
