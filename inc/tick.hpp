/*
 * tick.hpp
 */

#ifndef _TICK_HPP_
#define _TICK_HPP_

#include "units.hpp"

#include "threads.hpp"

struct ITick {
	virtual void tick(Engine::Units::Time) = 0;
};

class TickHandler {
public:
	TickHandler();
	TickHandler(ThreadPool*);
	void ~TickHandler();

	void registerITick(ITick*);
	void unregisterITick(ITick*);

	void setTickRate(int);
	int getTickRate();
	void setTickPeriod(Engine::Units::Time);
	Engine::Units::Time getTickPeriod;

	void start();
	void join(); //Allow next execution to finish
	void stop(); //Stop immediately

private:
	struct TickStatus {
		bool started; //Shows if the ITick has been scheduled
		bool active;  //Used to stop ITick from running
	};

	//Internal
	bool createdPool = false;
	ThreadPool *threadPool;
	TaskScheduler scheduler;

	//Register/Unregister
	std::map<ITick*,TickStatus> active;

	//Tick rate
	Engine::Units::Time tickPeriod;

	//Execution
	bool running;
	bool joining;
};

#endif
