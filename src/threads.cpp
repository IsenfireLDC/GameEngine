/*
 * threads.cpp
 */

#include "threads.hpp"

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
 * Spawned as a new thread to add to the thread pool
 */
void ThreadPool::taskHandler(ThreadPool *parent) {
	bool aquired;
	Task t;
	while(parent->running) {
		parent->lock.lock();

		if(parent->todo.size() <= 0) {
			parent->empty.wait(parent->lock);

			aquired = parent->running && !parent->joining;
		} else aquired = true;

		if(aquired) {
			t = parent->todo.front();
			parent->todo.pop();
		};
		parent->lock.unlock();

		if(aquired) t();
	};
};
