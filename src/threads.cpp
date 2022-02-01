/*
 * threads.cpp
 */

#include "threads.hpp"

Semaphore::Semaphore(int count = 1) {
	this->count = count;
};

void Semaphore::wait() {
	this->lock.lock();
	if(--count < 0) this->barrier.lock();
	this->lock.unlock();
};

void Semaphore::post() {
	this->lock.lock();
	if(count++ < 0) this->barrier.unlock();
	this->lock.unlock();
};

template<class Task>
ThreadPool<Task>::ThreadPool(int threads) {
	this->threads(threads);
};

template<class Task>
ThreadPool<Task>::~ThreadPool() {
	this->running = false;
};

template <class Task>
void ThreadPool<Task>::add(Task task) {
	this->todo.push(task);
};

template<class Task>
void ThreadPool<Task>::join() {
	for(std::thread *thread : this->threads)
		if(thread->joinable())
			thread->join();
};

template<class Task>
void ThreadPool<Task>::exit() {
	this->running = false;
};
