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

#include <unordered_map>

class Input {
public:
	Input();
	~Input();

	//Set the state of the key
	void setState(SDL_Keysym&, bool);

	//Get the state of the key from the scancode/keycode
	bool pressed(SDL_Scancode) const;
	bool pressed(SDL_Keycode) const;

	SDL_Keymod getModifiers() const;

private:
	static Log log;

	std::unordered_map<SDL_Scancode, bool> scancodes;
	std::unordered_map<SDL_Keycode, bool> keycodes;

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
