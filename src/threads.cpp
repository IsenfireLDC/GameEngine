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

ThreadPool::ThreadPool(int threads) {
	this->threads = std::vector<std::thread*>(threads);
};

ThreadPool::~ThreadPool() {
	this->running = false;
};

void ThreadPool::start() {
	this->running = true;

	for(unsigned int i = 0; i < threads.size(); ++i) {
		this->threads[i] = new std::thread(ThreadPool::taskHandler, this);
	};
};

void ThreadPool::add(Task task) {
	if(this->joining) return;

	Engine::log.log("Adding task to thread pool", Log::Entry::LogType::Debug, "ThreadPool:add");

	this->lock.lock();
	this->todo.push(task);

	this->lock.unlock();
	this->empty.notify_one();
};

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

void ThreadPool::exit() {
	this->running = false;
};

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
		Engine::log.log("Running task in thread pool", Log::Entry::LogType::Debug, "ThreadPool:taskHandler");
		t();
	};
};
