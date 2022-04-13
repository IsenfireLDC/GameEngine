/*
 * utils.hpp
 *
 * General utilities used throughout the program
 */

#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <string>

#include <thread>
#include <chrono>
#include <functional>
#include <mutex>

#include "engine_types.hpp"

namespace Utils {
	int nextID(int*);
	
	void create_directories(std::string);

	using Duration = Engine::Units::Time;

	typedef std::function<void(void*)> Callback;
	struct CallbackHandle {
		std::thread* thread;
		Duration period;
		Callback callback;
		bool repeat;
		bool wait;
		std::timed_mutex run;


		CallbackHandle(Duration period, Callback callback, bool repeat, bool wait) {
			this->thread = nullptr;
			this->period = period;
			this->callback = callback;
			this->repeat = repeat;
			this->wait = wait;
		};

		~CallbackHandle() {
			delete this->thread;
		};
	};

	CallbackHandle* scheduleAsyncCallback(Duration, Callback, bool, bool);
	void destroyAsyncCallback(CallbackHandle*);
};

#endif
