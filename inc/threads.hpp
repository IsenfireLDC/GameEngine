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
#include <condition_variable>

namespace mystd {
class semaphore {
public:
	semaphore(int);

	void wait();
	void post();
private:
	int count;

	std::mutex lock, barrier;
	std::condition_variable_any cv;
};
}; //namespace mystd

class ThreadPool {
public:
	using Task = std::function<void(void)>;

	ThreadPool(int);
	virtual ~ThreadPool();

	virtual void start();

	virtual void add(Task);
	virtual void join();
	virtual void exit();
private:
	std::queue<Task> todo;
	std::mutex lock;
	std::condition_variable_any empty;

	bool running = false;
	bool joining = false;

	std::vector<std::thread*> threads;
};

#endif
