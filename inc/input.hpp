/*
 * input.hpp
 *
 * Controls input
 */

#ifndef _INPUT_HPP_
#define _INPUT_HPP_

#include "events.hpp"
#include "log.hpp"

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>

#include <functional>
#include <unordered_map>

/*
 * Handles passing input to the program
 *
 * Allows using event-based input or polling
 */
class Input {
public:
	using Handler = std::function<void(SDL_KeyboardEvent*)>;
public:
	Input(bool = false);
	~Input();

	//Set handler for a key
	Input& setHandler(SDL_Scancode, Handler);

	//Get the state of the key from the scancode/keycode
	//TODO: Add explicit key tracking/untracking
	bool pressed(SDL_Scancode);
	bool pressed(SDL_Keycode);

	SDL_Keymod getModifiers() const;

private:
	static Log log;

	static int listener(void*, SDL_Event*);

	bool isPressed(SDL_Scancode) const;

	std::unordered_map<SDL_Scancode, bool> keys;
	std::unordered_map<SDL_Scancode, Input::Handler> handlers;

	SDL_Keymod modifiers;
};


//struct ActionEvent : Event {
//	Action action;
//	int input;
//
//	ActionEvent(Action action, int input) : Event() {
//		this->action = action;
//		this->input = input;
//	};
//
//	virtual int getHash() {
//		return Event_MgetHash(ActionEvent);
//	};
//
//	virtual std::string getInfo() {
//		char info[100];
//		void(**act)(Entity*,int) = this->action.target<void(*)(Entity*,int)>();
//		sprintf(info, "ActionEvent{action=%p;input=%d}", *act, this->input);
//		return std::string(info);
//	};
//};

//struct QuitEvent : Event {
//	Input *input;
//
//	QuitEvent(Input *input) : Event() {
//		this->input = input;
//	};
//
//	virtual int getHash() {
//		return Event_MgetHash(QuitEvent);
//	};
//
//	virtual std::string getInfo() {
//		char info[100];
//		sprintf(info, "QuitEvent{input=%p}", this->input);
//		return std::string(info);
//	};
//};

//TODO?: Create async handler for input with new event system

#endif
