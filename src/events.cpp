/*
 * events.cpp
 */

#include "events.hpp"

#include <typeinfo>

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

	if(this->eventIDs.contains(hash))
		return this->eventIDs[hash];
	else
		return -1;
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
