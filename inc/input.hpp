/*
 * input.hpp
 *
 * Controls input
 */

#ifndef _INPUT_HPP_
#define _INPUT_HPP_

#include "entity.hpp"

#include "events.hpp"

#include <functional>
#include <unordered_map>

typedef std::function<void(Entity*, int)> Action;
//typedef void(*Action)(Entity*, int);

extern Action MoveAction;
extern Action NoneAction;

extern const std::unordered_map<int, Action> defaultMap;

//Special key code
const int sKey = (224<<8);

class Input {
public:
	enum Key : int {
		W = 17,
		A = 30,
		S = 31,
		D = 32,
		Up = 72,
		Left = 75,
		Down = 80,
		Right = 77,
		Escape = 1,
		Null = 0
	};

	static int getInputKey();
	static int getInputScan();
	static int getKeyboardLayout();

	Input();
	Input(std::unordered_map<int, Action>);

	const Action getAction(int) const;
	bool callAction(Entity*, int) const;

	void addActionMapping(int, Action);
	void removeActionMapping(int);
private:
	std::unordered_map<int, Action> actionMap;
};

struct InputEvent : Event {
	Input::Key key;

	InputEvent(int trigger, Input::Key key) : Event(trigger) {
		this->key = key;
	};
};

//TODO?: Create async handler for input with new event system

#endif
