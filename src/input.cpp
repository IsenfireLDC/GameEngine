/*
 * input.cpp
 *
 * Controls input
 */

#include "input.hpp"

#include <conio.h>
#include <winuser.h>

#include "engine.hpp"

using LogType = Log::Entry::LogType;

Log Input::log{"Input", "./logs/input.log"};

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

Action MoveAction = aMove;

const std::unordered_map<int, Action> defaultMap = {
	{Input::Key::W, MoveAction},
	{Input::Key::A, MoveAction},
	{Input::Key::S, MoveAction},
	{Input::Key::D, MoveAction},
	{Input::Key::Up, MoveAction},
	{Input::Key::Left, MoveAction},
	{Input::Key::Down, MoveAction},
	{Input::Key::Right, MoveAction}
};

static INPUT_RECORD getInput(int timeout, HANDLE interruptHandle) {
	const int bufferSize = 10;

	DWORD mode;

	static INPUT_RECORD input[bufferSize];
	static int buffered = 0;

	HANDLE waitHandles[2] = {nullptr, interruptHandle};

	if(buffered == 0) {
		//Std handle
		HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);

		//Save current mode
		GetConsoleMode(handle, &mode);

		//Set mode
		SetConsoleMode(handle, 0);
		waitHandles[0] = handle;
		if(WaitForMultipleObjects(2, waitHandles, false, timeout) == WAIT_OBJECT_0) {
			DWORD cnt;

			//Get input event
			ReadConsoleInput(handle, input, bufferSize, &cnt);

			buffered = cnt;
		} else {
			input[0].EventType = 0;
			SetConsoleMode(handle, mode);
			return input[0];
		};

		SetConsoleMode(handle, mode);
	};


	INPUT_RECORD retVal = input[0];

	--buffered;

	for(int i = 0; i < buffered; ++i)
		input[i] = input[i+1];

	return retVal;
};

int Input::getInputKey() {
	INPUT_RECORD input = getInput(0, 0);

	if(input.EventType == KEY_EVENT)
		return getInput(0, 0).Event.KeyEvent.wVirtualKeyCode;

	return 0;
};

int Input::getInputScan() {
	INPUT_RECORD input = getInput(0, 0);

	if(input.EventType == KEY_EVENT)
		return getInput(0, 0).Event.KeyEvent.wVirtualScanCode;

	return 0;
};

Input::Input() : Input(defaultMap) {};

Input::Input(std::unordered_map<int, Action> actionMap) {
	this->actionMap = actionMap;

	this->intrHandle = CreateEventA(0, true, false, 0);
};

/*
 * Wait for thread to finish on delete
 */
Input::~Input() {
	this->active = false;

	PulseEvent(this->intrHandle);
	if(this->thread->joinable()) this->thread->join();
};

/*
 * Spawn a thread for this instance
 *
 * Returns if a thread exists after the call
 */
bool Input::spawnThread() {
	if(this->thread && this->thread->joinable()) return true;

	this->active = true;
	this->thread = new std::thread(&Input::threadHandler, this);
	
	return this->thread->joinable();
};

/*
 * Pause/resume the thread if it exists, otherwise return false
 */
bool Input::runThread(bool run) {
	if(!this->thread->joinable()) return false;

	//TODO: Pause/resume execution of thread
	this->active = run;
	return true;
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

/*
 * Input handler
 *
 * Thread exits on generating QuitEvent
 */
void Input::threadHandler() {
	Input::log.log("Input thread started", LogType::Info, "Handler");
	while(this->active) {
		INPUT_RECORD input = getInput(10000, this->intrHandle);
		int scanCode;

		if(input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown)
			scanCode = input.Event.KeyEvent.wVirtualScanCode;
		else
			scanCode = 0;
	
		const Action action = this->getAction(scanCode);

		Event *event;
		if(action) {
			event = new ActionEvent(action, scanCode);
		} else {
			switch(scanCode) {
				case Input::Key::Escape:
					event = new QuitEvent(this);
					break;
				case Input::Key::Null:
					continue;
				default:
					event = new InputEvent((Input::Key)scanCode);
			};
		};
		Engine::eventBus.queueEvent(event);

		Input::log.log("Received keypress", LogType::Debug, "Handler");
	
		//Select action and queue event
		//Have quit event contain pointer to Input
	}
};
