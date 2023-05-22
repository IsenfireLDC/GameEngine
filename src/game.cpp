/*
 * game.cpp
 */

#include "game.hpp"

#include "update.hpp"
#include "level.hpp"
#include "log.hpp"

#include "engine.hpp"

/*
 * Creates game with empty tickables set at 30 fps
 */
Game::Game() : updateController(&Engine::level, &Engine::threadPool)/*, scheduler(&Engine::threadPool)*/ {
	//this->setFPS(30);
};

Game::~Game() {
	this->run(false);
};

/*
 * Starts or stops ticking game objects
 */
void Game::run(bool run) {
	if(run) {
		Engine::log.log("Running game", LogLevel::Debug, "Game");
		if(!Engine::threadPool.isRunning())
			Engine::threadPool.start();

		this->running = true;

		Engine::threadPool.add(std::bind(Game::handler, this));
	} else
		this->joining = true;
};

/*
 * Function run by the scheduler that queues all ticks to the thread pool
 */
void Game::handler() {
	Engine::log.log("Scheduling task running", LogLevel::Debug, "TickHandler:scheduleTask");
	if(!this->running) return;

	static Engine::Units::TimePoint lastTick = Engine::Clock::now();

	//Ensure that the thread pool is running before we add tasks
	if(Engine::threadPool.isRunning()) {
		//Provide a measurement of the actual time delta
		Engine::Units::TimePoint tp = Engine::Clock::now();
	
		Engine::Units::Time passed = tp - lastTick;
	
		this->updateController.update((float)passed.count() / Engine::Units::Time::period::den);
	
		lastTick = tp;
	};

	std::this_thread::yield();

	//Reschedule task
	if(!this->joining)
		Engine::threadPool.add(std::bind(Game::handler, this));
		//this->scheduler.scheduleIn(
		//	this->schedulingTask,
		//	this->tickPeriod
		//);
	else
		this->running = false;
};




///*
// * Dequeues and calls event handler for all events in queue
// *
// * Is thread-safe with calls to queueEvent
// */
//void EventController::handleEvents() {
//	Engine::log.log("Handling queued events", LogLevel::Debug, "EventController");
//	while(this->events.size() > 0) {
//		this->eventsLock.lock();
//		Event *event = this->events.front();
//		this->events.pop();
//		this->eventsLock.unlock();
//
//		int id = this->getEventID(event);
//
//		this->handlers[id](event);
//
//		delete event;
//	};
//};
//
///*
// * Sets an event handler to be called for a given event
// *
// * Event type must be registered first with registerEventType
// *
// * The same event type cannot have more than one handler
// */
//void EventController::registerEventHandler(int eventID, EventHandler handler) {
//	Engine::log.log("Register event handler", LogLevel::Debug, "EventController");
//	this->handlers[eventID] = handler;
//};
