/*
 * tick.cpp
 */

#include "tick.hpp"

#include "threads.hpp"

#include <unordered_map>

#include "engine.hpp"

TickHandler::TickHandler() : TickHandler(new ThreadPool(5)) {
	this->createdPool = true;
};

TickHandler::TickHandler(ThreadPool *threadPool) : scheduler(threadPool) {
	this->threadPool = threadPool;

	this->schedulingTask = [this](){
		if(!this->running) return;

		//Monitor time
		Engine::Units::TimePoint tp = Engine::Clock::now();
	
		Engine::Units::Time passed = tp - this->lastTick;
	
		for(std::pair<ITick*const, TickStatus>& n : this->registered) {
			if(!n.second.active) continue;
			n.second.started = true;

			this->threadPool->add(std::bind(n.first->tick, n.first, passed));
		};
		this->scheduler.scheduleIn(this->schedulingTask, this->tickPeriod);
	
		this->lastTick = tp;
	
		//Reschedule task
		if(!this->joining)
			this->scheduler.scheduleIn(
				this->schedulingTask,
				this->tickPeriod
			);
		else
			this->running = false;
	};
};

TickHandler::~TickHandler() {
};

void TickHandler::registerITick(ITick *toTick) {
	//Add ITick to map, if it's not already there
	if(this->registered.count(toTick) == 0) {
		this->registered[toTick] = (TickStatus){false,true};
	};
};

/*
 * Removes toTick if it has not been scheduled
 * Otherwise, sets active flag to false; toTick will be removed by
 * the task lambda
 */
void TickHandler::unregisterITick(ITick *toTick) {
	if(this->registered[toTick].started)
		this->registered[toTick].active = false;
	else
		this->registered.erase(toTick);
};

/*
 * Set tickPeriod using a tick rate of ticks per second
 */
void TickHandler::setTickRate(int tickRate) {
	this->tickPeriod = Engine::Units::Time(
		Engine::Units::Time::period::den / tickRate
	);
};

/*
 * Get tick rate in ticks per second from tickPeriod
 *
 * TODO: Add rounding?
 */
int TickHandler::getTickRate() const {
	return Engine::Units::Time::period::den / this->tickPeriod.count();
};

void TickHandler::setTickPeriod(Engine::Units::Time tickPeriod) {
	this->tickPeriod = tickPeriod;
};

Engine::Units::Time TickHandler::getTickPeriod() const {
	return this->tickPeriod;
};

/*
 * Start ticking registered ITick instances
 *
 * Starts the ThreadPool if it wasn't already running
 */
void TickHandler::start() {
	this->running = true;
	this->joining = false;
	for(std::pair<ITick*const, TickStatus>& n : this->registered) {
		n.second.active = true;
	};

	if(!this->threadPool->isRunning())
		this->threadPool->start();
};

/*
 * Stops running after the next tick completes
 *
 * Will not join with the ThreadPool unless it was created by the TickHandler
 */
void TickHandler::join() {
	this->joining = true;

	//The running flag will be unset in the tick handler
	while(this->running)
		std::this_thread::yield();

	if(this->createdPool)
		this->threadPool->join();
};

void TickHandler::stop() {
	this->running = false;
	this->joining = true;
};

bool TickHandler::active() const {
	return this->running;
};
