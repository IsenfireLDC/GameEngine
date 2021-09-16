/*
 * input.cpp
 *
 * Controls input
 */

#include "input.hpp"

#include <conio.h>
#include <winuser.h>

static void aMove(Entity *target, int input) {
	Coord ePos = target->getPos();

	switch (input) {
		case Input::Key::W:
		case Input::Key::Up:
			ePos = ePos + Coord(0,-1);
			break;
		case Input::Key::A:
		case Input::Key::Left:
			ePos = ePos + Coord(-1,0);
			break;
		case Input::Key::S:
		case Input::Key::Down:
			ePos = ePos + Coord(0,1);
			break;
		case Input::Key::D:
		case Input::Key::Right:
			ePos = ePos + Coord(1,0);
			break;
	};

	target->move(ePos);
};

static void aNone(Entity *target, int input) {};

Action MoveAction = aMove;
Action NoneAction = aNone;

const std::unordered_map<int, Action> defaultMap = {
	{Input::Key::W, MoveAction},
	{Input::Key::A, MoveAction},
	{Input::Key::S, MoveAction},
	{Input::Key::D, MoveAction},
	{Input::Key::Up, MoveAction},
	{Input::Key::Left, MoveAction},
	{Input::Key::Down, MoveAction},
	{Input::Key::Right, MoveAction},
	{Input::Key::Null, NoneAction}
};

static INPUT_RECORD getInput() {
	DWORD mode;
	INPUT_RECORD input;

	//Std handle
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);

	//Save current mode
	GetConsoleMode(handle, &mode);

	//Set mode
	SetConsoleMode(handle, 0);

	if(WaitForSingleObject(handle, 0) == WAIT_OBJECT_0) {
		DWORD cnt;

		//Get input event
		ReadConsoleInput(handle, &input, 1, &cnt);
	};

	SetConsoleMode(handle, mode);
	return input;
};

int Input::getInputKey() {
	INPUT_RECORD input = getInput();

	if(input.EventType == KEY_EVENT)
		return getInput().Event.KeyEvent.wVirtualKeyCode;

	return 0;
};

int Input::getInputScan() {
	INPUT_RECORD input = getInput();

	if(input.EventType == KEY_EVENT)
		return getInput().Event.KeyEvent.wVirtualScanCode;

	return 0;
};


Input::Input() {
	this->actionMap = defaultMap;
};

Input::Input(std::unordered_map<int, Action> actionMap) {
	this->actionMap = actionMap;
};

/*
 * Get the Action associated with input
 */
const Action Input::getAction(int input) const {
	if(this->actionMap.find(input) != this->actionMap.end())
		return this->actionMap.at(input);

	return nullptr;
};

/*
 * Call an action on target (automatically resolves action)
 */
bool Input::callAction(Entity *target, int input) const {
	Action a = this->getAction(input);

	if(a) {
		a(target, input);
		return true;
	} else return false;
};

/*
 * Inserts or updates the Action mapped to input
 */
void Input::addActionMapping(int input, Action action) {
	this->actionMap[input] = action;
};

/*
 * Removes the Action mapped to input
 */
void Input::removeActionMapping(int input) {
	if(this->actionMap.find(input) != this->actionMap.end())
		this->actionMap.erase(input);
};

