/*
 * utils.cpp
 *
 * General utilities
 */

#include "utils.hpp"

//#include <sys/stat.h>
//#include <direct.h> //Thanks, windows
#include <fileapi.h>

/*
 * Spawns a thread to run the callback function at regular intervals
 *
 * If wait is false, it is possible that the last thread has not completed when
 * the next is spawned
 */
static void _callbackHandler(Utils::CallbackHandle *handle) {
	do {
		std::thread t{handle->callback, handle};
		if(handle->wait) t.join();
		else t.detach();
	} while(handle->repeat && !handle->run.try_lock_for(handle->period));

	//Destroy the reference to the thread
	delete handle->thread;
};



namespace Utils {

int nextID(int *tracker) {
	int r = *tracker;
	*tracker += 1;
	return r;
};

void create_directories(std::string path) {
	size_t pos = 0;

	while(pos != std::string::npos) {
		pos = path.find("/", pos+1);
		CreateDirectoryA(path.substr(0, pos).c_str(), nullptr);
	};
};

CallbackHandle* scheduleAsyncCallback(Duration period, Callback callback, bool repeat = false, bool wait = true) {
	CallbackHandle *handle = new CallbackHandle(period, callback, repeat, wait);

	handle->run.lock();
	handle->thread = new std::thread(_callbackHandler, handle);

	return handle;
};

void destroyAsyncCallback(CallbackHandle *handle) {
	handle->run.unlock();

	delete handle;
};

};
