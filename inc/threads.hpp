/*
 * threads.hpp
 */

#ifndef _THREADS_HPP_
#define _THREADS_HPP_

#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <vector>

class Semaphore {
public:
	Semaphore(int);

	void wait();
	void post();
private:
	int count;

	std::mutex lock, barrier;
};

template<class Task = std::function<void(void)>>
class ThreadPool {
public:
	ThreadPool(int);
	~ThreadPool();

	void add(Task);
	void join();
	void exit();
private:
	std::queue<Task> todo;

	bool running;

	std::vector<std::thread*> threads;
};

#endif
