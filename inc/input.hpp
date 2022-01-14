/*
 * input.hpp
 *
 * Controls input
 */

#ifndef _INPUT_HPP_
#define _INPUT_HPP_

#include "entity.hpp"

#include "events.hpp"
#include "log.hpp"

#include <functional>
#include <unordered_map>

#include <thread>

#include <string>

typedef std::function<void(Entity*, int)> Action;
//typedef void(*Action)(Entity*, int);

extern Action MoveAction;

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

	~Input();

	bool spawnThread();
	bool runThread(bool);

	const Action getAction(int) const;
	bool callAction(Entity*, int) const;

	void addActionMapping(int, Action);
	void removeActionMapping(int);

private:
	static Log log;
	void threadHandler();

	std::unordered_map<int, Action> actionMap;

	std::thread *thread = nullptr;

	int timeout = 200;
	bool active = false;
};

struct InputEvent : Event {
	Input::Key key;

	InputEvent(Input::Key key) : Event() {
		this->key = key;
	};

	virtual int getHash() {
		return Event_MgetHash(InputEvent);
	};

	virtual std::string getInfo() {
		char info[100];
		sprintf(info, "InputEvent{key=%d}", this->key);
		return std::string(info);
	};
};

struct ActionEvent : Event {
	Action action;
	int input;

	ActionEvent(Action action, int input) : Event() {
		this->action = action;
		this->input = input;
	};

	virtual int getHash() {
		return Event_MgetHash(ActionEvent);
	};

	virtual std::string getInfo() {
		char info[100];
		void(**act)(Entity*,int) = this->action.target<void(*)(Entity*,int)>();
		sprintf(info, "ActionEvent{action=%p;input=%d}", *act, this->input);
		return std::string(info);
	};
};

struct QuitEvent : Event {
	Input *input;

	QuitEvent(Input *input) : Event() {
		this->input = input;
	};

	virtual int getHash() {
		return Event_MgetHash(QuitEvent);
	};

	virtual std::string getInfo() {
		char info[100];
		sprintf(info, "QuitEvent{input=%p}", this->input);
		return std::string(info);
	};
};

//TODO?: Create async handler for input with new event system

#endif
