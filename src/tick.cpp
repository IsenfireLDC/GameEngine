/*
 * tick.cpp
 */

#include "tick.hpp"

#include "units.hpp"
#include "threads.hpp"

#include <unordered_map>

TickHandler::TickHandler() : TickHandler(new ThreadPool(5)) {
	this->createdPool = true;
};

TickHandler::TickHandler(ThreadPool *threadPool) : scheduler(threadPool) {
	this->threadPool = threadPool;
};

TickHandler::~TickHandler() {
};

void TickHandler::registerITick(ITick *toTick) {
	//Add ITick to map, if it's not already there
	if(this->active.count(toTick) == 0) {
		this->active[toTick] = (TickStatus){false,true,Engine::Clock::now(),nullptr};

		TaskScheduler<>::Task *f = new TaskScheduler<>::Task();
		*f = [this, toTick](){
			TickStatus &status = this->active[toTick];

			//Allow cancelation
			if(!status.active) return;
		
			//Monitor time
			Engine::Units::TimePoint tp = Engine::Clock::now();
		
			Engine::Units::Time passed = tp - status.lastTick;
			toTick->tick(passed);
		
			status.lastTick = tp;
		
			//Reschedule task
			this->scheduler.scheduleIn(*status.recurse, this->tickPeriod);
		};

		this->active[toTick].recurse = f;
	};
};

/*
 * Removes toTick if it has not been scheduled
 * Otherwise, sets active flag to false; toTick will be removed by
 * the task lambda
 */
void TickHandler::unregisterITick(ITick *toTick) {
	if(this->active[toTick].started)
		this->active[toTick].active = false;
	else
		this->active.erase(toTick);
};

/*
 * Set tickPeriod using a tick rate of ticks per second
 */
void TickHandler::setTickRate(int tickRate) {
	this->tickPeriod = Engine::Units::Time::period::denom / tickRate;
};

/*
 * Get tick rate in ticks per second from tickPeriod
 *
 * TODO: Add rounding?
 */
int TickHandler::getTickRate() {
	return Engine::Units::Time::period::denom / this->tickPeriod.count();
};

void TickHandler::setTickPeriod(Engine::Units::Time tickPeriod) {
	this->tickPeriod = tickPeriod;
};

Engine::Units::Time TickHandler::getTickPeriod() {
	return this->tickPeriod;
};

void TickHandler::start() {
	this->running = true;
	this->joining = false;
	for(const std::pair<ITick*, TickStatus>& n : this->active) {
		n.second.active = true;
		n.second.started = true;
		this->scheduler.scheduleIn(*n.second.recurse, this->tickPeriod);
	};
};

void TickHandler::join() {
	this->joining = true;
};

void TickHandler::stop() {
	this->running = false;
	this->joining = true;
};
