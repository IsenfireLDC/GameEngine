/*
 * tick.hpp
 */

#ifndef _TICK_HPP_
#define _TICK_HPP_

#include "threads.hpp"

#include <unordered_map>

#include "engine_types.hpp"

struct ITick {
	virtual void tick(Engine::Units::Time) = 0;
};

class TickHandler {
public:
	TickHandler();
	TickHandler(ThreadPool*);
	~TickHandler();

	void registerITick(ITick*);
	void unregisterITick(ITick*);

	void setTickRate(int);
	int getTickRate() const;
	void setTickPeriod(Engine::Units::Time);
	Engine::Units::Time getTickPeriod() const;

	void start();
	void join(); //Allow next execution to finish
	void stop(); //Stop immediately

	bool active() const;

private:
	struct TickStatus {
		bool started; //Shows if the ITick has been scheduled
		bool active;  //Used to stop ITick from running
	};

	//Internal
	bool createdPool = false;
	ThreadPool *threadPool;
	TaskScheduler<> scheduler;
	TaskScheduler<>::Task schedulingTask;
	Engine::Units::TimePoint lastTick;

	//Register/Unregister
	std::unordered_map<ITick*,TickStatus> registered;

	//Tick rate
	Engine::Units::Time tickPeriod;

	//Execution
	bool running;
	bool joining;
};

#endif

/*
Task scheduling lambda must reschedule itself
TSL must have a check for join/exit
Will there be an issue if start is called quickly after exit?
 - Create a new priority queue container that supports removal?
*/
