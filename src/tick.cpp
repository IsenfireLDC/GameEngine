/*
 * tick.cpp
 */

#include "tick.hpp"

#include "threads.hpp"

#include <unordered_map>

#include "log.hpp"

#include "engine.hpp"

TickHandler::TickHandler() : TickHandler(new ThreadPool(5)) {
	this->createdPool = true;
};

TickHandler::TickHandler(ThreadPool *threadPool) : scheduler(threadPool) {
	Engine::log.log("Created new TickHandler", Log::Entry::LogType::Debug, "TickHandler");
	this->threadPool = threadPool;

};

TickHandler::~TickHandler() {
};

void TickHandler::registerITick(ITick *toTick) {
	Engine::log.log("Registered new ITick", Log::Entry::LogType::Debug, "TickHandler");
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
	Engine::log.log("Unregistered ITick", Log::Entry::LogType::Debug, "TickHandler");
	if(this->registered[toTick].started)
		this->registered[toTick].active = false;
	else
		this->registered.erase(toTick);
};

/*
 * Set tickPeriod using a tick rate of ticks per second
 */
void TickHandler::setTickRate(int tickRate) {
	Engine::log.log("Set tick rate", Log::Entry::LogType::Debug, "TickHandler");
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
	Engine::log.log("Set tick period", Log::Entry::LogType::Debug, "TickHandler");
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
	Engine::log.log("Starting ticking registered ITick's", Log::Entry::LogType::Debug, "TickHandler");
	this->running = true;
	this->joining = false;
	for(std::pair<ITick*const, TickStatus>& n : this->registered) {
		n.second.active = true;
	};

	this->schedulingTask = std::bind(TickHandler::scheduleTask, this);

	if(!this->threadPool->isRunning())
		this->threadPool->start();

	this->threadPool->add(this->schedulingTask);
};

/*
 * Stops running after the next tick completes
 *
 * Will not join with the ThreadPool unless it was created by the TickHandler
 */
void TickHandler::join() {
	Engine::log.log("Joining with thread pool", Log::Entry::LogType::Debug, "TickHandler");
	this->joining = true;

	//The running flag will be unset in the tick handler
	while(this->running)
		std::this_thread::yield();

	if(this->createdPool)
		this->threadPool->join();
};

void TickHandler::stop() {
	Engine::log.log("Stopping thread pool", Log::Entry::LogType::Debug, "TickHandler");
	this->running = false;
	this->joining = true;
};

bool TickHandler::active() const {
	return this->running;
};


void TickHandler::scheduleTask(TickHandler *parent) {
	Engine::log.log("Scheduling task running", Log::Entry::LogType::Debug, "TickHandler:scheduleTask");
	if(!(parent && parent->running)) return;

	//Monitor time
	Engine::Units::TimePoint tp = Engine::Clock::now();

	Engine::Units::Time passed = tp - parent->lastTick;

	for(std::pair<ITick*const, TickStatus>& n : parent->registered) {
		if(!n.second.active) continue;
		n.second.started = true;

		parent->threadPool->add(std::bind(n.first->tick, n.first, passed));
	};

	parent->lastTick = tp;

	//Reschedule task
	if(!parent->joining)
		parent->scheduler.scheduleIn(
			parent->schedulingTask,
			parent->tickPeriod
		);
	else
		parent->running = false;
};
