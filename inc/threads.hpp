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

#include <chrono>

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

	bool isRunning() const;

	static void taskHandler(ThreadPool*);

private:
	std::queue<Task> todo;
	std::mutex lock;
	std::condition_variable_any empty;

	bool running = false;
	bool joining = false;

	std::vector<std::thread*> threads;
};

template<class Time = std::chrono::system_clock::time_point>
class TaskScheduler {
public:
	using Task = std::function<void(void)>;
	using PTask = std::pair<Time, Task>;

	struct gtTask {
		bool operator()(PTask &t1, PTask &t2) {
			return t1.first > t2.first;
		};
	};

	TaskScheduler(ThreadPool*);
	~TaskScheduler();

	void join();

	template<class R, class P>
	void scheduleIn(Task, const std::chrono::duration<R,P>&);

	template<class C, class D>
	void scheduleAt(Task, const std::chrono::time_point<C,D>&);

	static void schedulingTask(TaskScheduler<Time>*);

private:
	std::priority_queue<PTask, std::vector<PTask>, gtTask> tasks;

	ThreadPool *threadPool;

	std::mutex lock;
	std::timed_mutex barrier;
	std::condition_variable_any cv;

	std::thread *thread;

	bool running;
};


/* TEMPLATE DEFINITION */

// Task Scheduler


template<class T>
TaskScheduler<T>::TaskScheduler(ThreadPool *threadPool) {
	this->threadPool = threadPool;

	this->barrier.lock();
	this->running = true;

	this->thread = new std::thread(TaskScheduler<T>::schedulingTask, this);
};

template<class T>
TaskScheduler<T>::~TaskScheduler() {
	this->running = false;
	this->barrier.unlock();
	this->cv.notify_all();

	this->thread->join();
	delete this->thread;
};

template<class T>
void TaskScheduler<T>::join() {
	this->running = false;

	this->thread->join();
};

template<class T>
template<class R, class P>
void TaskScheduler<T>::scheduleIn(Task task, const std::chrono::duration<R,P> &in) {
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	T time = now + in;

	this->lock.lock();
	this->tasks.push(PTask(time, task));
	this->lock.unlock();

	this->cv.notify_one();
};

template<class T>
template<class C, class D>
void TaskScheduler<T>::scheduleAt(Task task, const std::chrono::time_point<C,D> &at) {
	this->lock.lock();
	this->tasks.push(at, task);
	this->lock.unlock();

	this->cv.notify_one();
};

template<class T>
void TaskScheduler<T>::schedulingTask(TaskScheduler<T> *parent) {
	while(1) {
		parent->lock.lock();
		while(parent->tasks.empty()) {
			if(!parent->running) {
				parent->lock.unlock();
				return;
			};

			parent->cv.wait(parent->lock);
		};

		PTask next = parent->tasks.top();
		parent->tasks.pop();
		parent->lock.unlock();

		if(parent->barrier.try_lock_until(next.first)) {
			parent->barrier.unlock();
			return;
		}

		parent->threadPool->add(next.second);
	};
};

#endif
