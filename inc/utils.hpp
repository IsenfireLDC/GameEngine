/*
 * utils.hpp
 *
 * General utilities used throughout the program
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>

#include <thread>
#include <chrono>
#include <functional>
#include <mutex>

namespace Utils {
	int nextID(int*);
	
	void create_directories(std::string);

	using Duration = std::chrono::microseconds;

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

#define Utils__FPS(fps) std::chrono::duration<int, std::ratio<1, fps>>(1)
	//template<std::intmax_t fps>  //How do you do that w/o a macro?
	//std::chrono::duration<int, std::ratio<1, fps>>;
};

#endif
