/*
 * events.hpp
 *
 * Events used to queue inputs and interactions
 */

#ifndef _EVENTS_HPP_
#define _EVENTS_HPP_

#include "utils.hpp"

#include <functional>
#include <unordered_map>
#include <queue>
#include <mutex>

#include <string>

/*
 * Basic Event List:
 * ============================================================================
 * InputEvent		: General un-mapped input
 * QuitEvent		: Close game
 * ActionEvent		: Action to handle (maybe just use event handler?)
 * CollisionEvent	: Entity attempted to move onto another
 * MoveEvent		: Moved an entity
 */

/*
 * Event needs:
 *  - type of event -> how to handle
 *  - data -> what to do
 *    - sender
 *    - message
 */

/*
 * Event:
 *  - Trigger	: class?/id?	: Who sent this?/Why was this sent?
 *  - Metadata	: members	: What is this?
 *    - Id			: Event type
 *    - Data			: Event data/context
 *  - Blocking?	: member	: Should I wait?
 *
 * On trigger, send event to queue:
 *  - Set approprate metedata
 *  - Check return data
 *    - If none; continue execution
 *    - Else wait for response
 *
 * Handle event:
 *  - Check for registered handler
 *    - If handler exists, call it
 *    - ElseIf default handler exists, call it
 *    - Else ignore
 *  - If something is waiting on the event, notify it
 */

#define Event_MgetHash(x) typeid(x).hash_code()

struct Event {
	friend class Events;

	Event() {};
	virtual ~Event();

	virtual int getHash() = 0;
	virtual std::string getInfo() = 0;
};

typedef std::function<void(Event*)> EventHandler;

class Events {
public:
	int registerEventType(Event*);
	int getEventID(Event*);

	void queueEvent(Event*);
	void handleEvents();

	Event* getFirstEvent() const {
		if(this->events.size()>0)
			return this->events.front();
		return nullptr;
	};

	void registerEventHandler(int, EventHandler);

private:
	std::unordered_map<int, EventHandler> handlers;
	std::unordered_map<int, int> eventIDs;

	std::queue<Event*> events;
	std::mutex eventsLock;

	static int gID;
};

#endif
