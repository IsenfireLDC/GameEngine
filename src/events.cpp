/*
 * events.cpp
 */

#include "events.hpp"

#include <typeinfo>

#include "log.hpp"

#include "engine.hpp"

//Engine event bus (global)
Events Engine::eventBus;

int Events::gID = 0;

//Does not link correctly with destructor in header file
Event::~Event() {};

/*
 * Checks if an event type has an id
 * If not, registers the event with a new id
 *
 * In both cases, the id of the event is returned
 */
int Events::registerEventType(Event *event) {
	Engine::log.log("Registering new event type", Log::Entry::LogType::Debug, "Events");
	int eventID = this->getEventID(event);
	if(eventID < 0) {
		eventID = Utils::nextID(&Events::gID);
		this->eventIDs[event->getHash()] = eventID;
	};

	return eventID;
};

/*
 * Searches the event IDs map for the given event and returns the id if found.
 * Otherwise, returns -1
 */
int Events::getEventID(Event *event) {
	int hash = event->getHash();

	if(this->eventIDs.find(hash) != this->eventIDs.end())
		return this->eventIDs[hash];
	else
		return -1;
};

/*
 * Queues an event to be handled
 *
 * May be called by other threads
 */
void Events::queueEvent(Event *event) {
	this->eventsLock.lock();
	this->events.push(event);
	this->eventsLock.unlock();
};

/*
 * Dequeues and calls event handler for all events in queue
 *
 * Is thread-safe with calls to queueEvent
 */
void Events::handleEvents() {
	Engine::log.log("Handling queued events", Log::Entry::LogType::Debug, "Events");
	while(this->events.size() > 0) {
		this->eventsLock.lock();
		Event *event = this->events.front();
		this->events.pop();
		this->eventsLock.unlock();

		int id = this->getEventID(event);

		this->handlers[id](event);

		delete event;
	};
};

/*
 * Sets an event handler to be called for a given event
 *
 * Event type must be registered first with registerEventType
 *
 * The same event type cannot have more than one handler
 */
void Events::registerEventHandler(int eventID, EventHandler handler) {
	Engine::log.log("Register event handler", Log::Entry::LogType::Debug, "Events");
	this->handlers[eventID] = handler;
};
