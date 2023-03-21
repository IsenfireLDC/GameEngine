/*
 * tick.cpp
 */

#include "tick.hpp"

#include "threads.hpp"

#include <unordered_map>

#include "log.hpp"

#include "engine.hpp"

/*
 * Default Constructor
 *
 * Create TickHandler using the default thread pool
 */
TickHandler::TickHandler() : TickHandler(&Engine::threadPool) {};

/*
 * Constructor
 *
 * Create TickHandler using an existing ThreadPool
 */
TickHandler::TickHandler(ThreadPool *threadPool) : scheduler(threadPool) {
	Engine::log.log("Created new TickHandler", LogLevel::Debug, "TickHandler");
	this->threadPool = threadPool;

};

/*
 * Destructor
 */
TickHandler::~TickHandler() {
};

/*
 * Enables ticking on toTick
 *
 * This will call the `tick` method of the ITick at the current tick rate
 * Readding an existing ITick will do nothing
 */
void TickHandler::enable(ITick *toTick) {
	Engine::log.log("Enable ITick", LogLevel::Debug, "TickHandler");
	//Add ITick to map, if it's not already there
	if(this->registered.count(toTick) == 0) {
		this->registered[toTick] = (TickStatus){false,true};
	};
};

/*
 * Disable ticking on toTick
 *
 * Removes toTick if it has not been scheduled
 * Otherwise, sets active flag to false; toTick will be removed by the scheduler
 */
void TickHandler::disable(ITick *toTick) {
	Engine::log.log("Disable ITick", LogLevel::Debug, "TickHandler");
	if(this->registered[toTick].started)
		this->registered[toTick].active = false;
	else
		this->registered.erase(toTick);
};

/*
 * Set tickPeriod using a tick rate of ticks per second
 */
void TickHandler::setTickRate(int tickRate) {
	Engine::log.log("Set tick rate", LogLevel::Debug, "TickHandler");
	this->tickPeriod = Engine::Units::Time(
		Engine::Units::Time::period::den / tickRate
	);
};

/*
 * Get tick rate in ticks per second from tickPeriod
 *
 * This rate is calculated from the internally stored period
 * TODO: Add rounding?
 */
int TickHandler::getTickRate() const {
	return Engine::Units::Time::period::den / this->tickPeriod.count();
};

/*
 * Set the tick period using the engine's standard time units
 *
 * All registered ITicks will be ticked every tickPeriod time units
 */
void TickHandler::setTickPeriod(Engine::Units::Time tickPeriod) {
	Engine::log.log("Set tick period", LogLevel::Debug, "TickHandler");
	this->tickPeriod = tickPeriod;
};

/*
 * Get the tick period in the engine's standard time units
 */
Engine::Units::Time TickHandler::getTickPeriod() const {
	return this->tickPeriod;
};

/*
 * Start ticking registered ITick instances
 *
 * The thread pool must be running for this to have an effect
 */
void TickHandler::start() {
	Engine::log.log("Starting ticking registered ITick's", LogLevel::Debug, "TickHandler");
	//Initialize running flags
	this->running = true;
	this->joining = false;

	//Set all currently registered items to active; this allows them to be run by the scheduler
	for(std::pair<ITick*const, TickStatus>& n : this->registered) {
		n.second.active = true;
	};

	this->schedulingTask = std::bind(TickHandler::scheduleTask, this);

	this->lastTick = Engine::Clock::now();

	this->threadPool->add(this->schedulingTask);
};

/*
 * Stops running after the next tick completes
 *
 * Will not join with the ThreadPool unless it was created by the TickHandler
 */
void TickHandler::join() {
	Engine::log.log("Joining with thread pool", LogLevel::Debug, "TickHandler");
	this->joining = true;

	//The running flag will be unset in the tick handler
	while(this->running)
		std::this_thread::yield();
};

/*
 * Stops running immediately
 */
void TickHandler::stop() {
	Engine::log.log("Stopping thread pool", LogLevel::Debug, "TickHandler");
	this->running = false;
	this->joining = true;
};

/*
 * Returns the value of the running flag
 */
bool TickHandler::active() const {
	return this->running;
};


/*
 * Function run by the scheduler that queues all ticks to the thread pool
 */
void TickHandler::scheduleTask(TickHandler *parent) {
	Engine::log.log("Scheduling task running", LogLevel::Debug, "TickHandler:scheduleTask");
	if(!(parent && parent->running)) return;

	//Ensure that the thread pool is running before we add tasks
	if(parent->threadPool->isRunning()) {
		//Provide a measurement of the actual time delta
		Engine::Units::TimePoint tp = Engine::Clock::now();
	
		Engine::Units::Time passed = tp - parent->lastTick;
	
		for(std::pair<ITick*const, TickStatus>& n : parent->registered) {
			if(!n.second.active) {
				if(n.second.started) { //These flags mean it should be removed
					parent->registered.erase(n.first);
				};
	
				//Don't run items that are inactive
				continue;
			};
	
			n.second.started = true;
	
			parent->threadPool->add(std::bind(n.first->tick, n.first, passed));
		};
	
		parent->lastTick = tp;
	};

	//Reschedule task
	if(!parent->joining)
		parent->scheduler.scheduleIn(
			parent->schedulingTask,
			parent->tickPeriod
		);
	else
		parent->running = false;
};
