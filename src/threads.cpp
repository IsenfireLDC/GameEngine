/*
 * threads.cpp
 */

#include "threads.hpp"

#include <sstream>
#include "log.hpp"

#include "engine.hpp"

//Default global thread pool
ThreadPool Engine::threadPool{10};

namespace mystd {

semaphore::semaphore(int count = 1) {
	this->count = count;
};

void semaphore::wait() {
	this->lock.lock();
	--count;
	this->lock.unlock();

	if(count < 0) cv.wait(this->barrier);
};

void semaphore::post() {
	if(count < 0) cv.notify_one();

	this->lock.lock();
	++count;
	this->lock.unlock();
};

}; //namespace mystd



/***** Thread Pool *****/

ThreadPool::ThreadPool(int threads) {
	this->threads = std::vector<std::thread*>(threads);
};

ThreadPool::~ThreadPool() {
	this->running = false;
};

/*
 * Starts the thread pool
 *
 * This method will instantiate all threads in the pool
 */
void ThreadPool::start() {
	this->running = true;

	for(unsigned int i = 0; i < threads.size(); ++i) {
		this->threads[i] = new std::thread(ThreadPool::taskHandler, this);
	};
};

/*
 * Adds a new task to the thread pool
 *
 * Tasks are queued, and run as soon as possible
 * Cannot add tasks if joining with the thread pool
 */
void ThreadPool::add(Task task) {
	if(this->joining) return;

	Engine::log.log("Adding task to thread pool", LogLevel::Debug, "ThreadPool:add");

	this->lock.lock();
	this->todo.push(task);

	this->lock.unlock();
	this->empty.notify_one();
};

/*
 * Joins with all threads in the pool
 *
 * Will run all remaining queued tasks before stopping pool
 * New tasks can not be added when joining
 *
 * After stopping or joining, all threads will exit
 */
void ThreadPool::join() {
	this->joining = true;

	while(this->todo.size() > 0)
		std::this_thread::yield();

	this->running = false;
	this->empty.notify_all();

	for(std::thread *thread : this->threads)
		if(thread->joinable())
			thread->join();
};

/*
 * Exits the thread pool immediately
 *
 * Will not run any more queued tasks, but cannot kill any tasks in progress
 *
 * After stopping or joining, all threads will exit
 */
void ThreadPool::exit() {
	this->running = false;
};

/*
 * Returns the running status of the thread pool
 */
bool ThreadPool::isRunning() const {
	return this->running;
};

/*
 * Dequeues and runs a task for the parent thread pool
 *
 * Spawned as a thread in the pool
 */
void ThreadPool::taskHandler(ThreadPool *parent) {
	Task t;
	while(parent->running) {
		parent->lock.lock();

		//Loop to avoid popping from the queue when there are no elements (Issue #15)
		while(parent->todo.size() <= 0) {
			parent->empty.wait(parent->lock);

			//All threads are notified when joining/stopping the thread pool
			//This will stop this thread from running if the thread pool stops
			if(!parent->running || parent->joining) {
				parent->lock.unlock();
				return;
			};
		};

		//Pop the next task from the queue
		t = parent->todo.front();
		parent->todo.pop();

		parent->lock.unlock();

		//Run the task after unlocking the pool
		Engine::log.log("Running task in thread pool", LogLevel::Debug, "ThreadPool:taskHandler");
		t();
	};
};
