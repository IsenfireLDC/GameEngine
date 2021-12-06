/*
 * events.cpp
 */

#include "events.hpp"

#include <typeinfo>

Events Engine::eventBus;

int Events::gID = 0;

/*
 * Gets the type hash of the event
 *
 * Used to get the key in the id mapping
 */
static int getHash(Event event) {
	return typeid(event).hash_code();
};

/*
 * Checks if an event type has an id
 * If not, registers the event with a new id
 *
 * In both cases, the id of the event is returned
 */
int Events::registerEventType(Event event) {
	int eventID = this->getEventID(event);
	if(eventID < 0) {
		eventID = Utils::nextID(&Events::gID);
		this->eventIDs[getHash(event)] = eventID;
	};

	return eventID;
};

/*
 * Searches the event IDs map for the given event and returns the id if found.
 * Otherwise, returns -1
 */
int Events::getEventID(Event event) {
	int hash = getHash(event);

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
void Events::queueEvent(Event event) {
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
	while(this->events.size() > 0) {
		this->eventsLock.lock();
		Event event = this->events.front();
		this->events.pop();
		this->eventsLock.unlock();

		int id = getEventID(event);

		handlers[id](event);
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
	this->handlers[eventID] = handler;
};
