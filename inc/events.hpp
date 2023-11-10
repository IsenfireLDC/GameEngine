/*
 * events.hpp
 *
 * Events used to queue inputs and interactions
 */

#ifndef _EVENTS_HPP_
#define _EVENTS_HPP_

#include <SDL2/SDL_events.h>

#include <string>

class EventBase {
public:
//	virtual unsigned int eventID() const = 0;

	virtual std::string getInfo() = 0;
};

template<typename T>
class Event : public EventBase {
public:
	static const unsigned int id;

	Event();
	virtual ~Event();

	virtual void setInfo(std::string);
	virtual std::string getInfo();

	/*
	 * These arguments are part of the SDL_UserEvent struct
	 *
	 * The remaining data member of the struct will have a pointer to the Event object
	 */
	void push(int = 0, void* = nullptr) const;

private:
	std::string info;
//private:
//	unsigned int eventID() const { return Event<T>::id; };
};


/********** TEMPLATE METHODS **********/

/*
 * Uses lazy initialization of static members to automatically register the class
 */
template<typename T>
const unsigned int Event<T>::id = SDL_RegisterEvents(1);

template<typename T>
Event<T>::Event() {};

template<typename T>
Event<T>::~Event() {};

template<typename T>
void Event<T>::setInfo(std::string info) {
	this->info = info;
};

template<typename T>
std::string Event<T>::getInfo() {
	return this->info;
};

/*
 * Push event to SDL event queue
 *
 * Passes SDL_UserEvent with these members:
 * 	type	: Event id
 * 	code	: <code> argument (default: 0)
 * 	data1	: Event object
 * 	data2	: <data> argument (default: nullptr)
 */
template<typename T>
void Event<T>::push(int code, void *data) const {
	SDL_UserEvent event = {
		.type = Event<T>::id,
		.code = code,
		.data1 = this,
		.data2 = data
	};

	SDL_PushEvent((SDL_Event*)&event);
};

#endif
