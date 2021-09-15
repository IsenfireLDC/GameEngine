/*
 * input.cpp
 *
 * Controls input
 */

#include "input.hpp"

#include <conio.h>

enum Input::Key : int {
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	Up = sKey|72,
	Left = sKey|75,
	Down = sKey|80,
	Right = sKey|77
};

static void aMove(Entity *target, int input) {
	Coord ePos = target->getPos();

	switch (input) {
		case Input::Key::W:
		case Input::Key::Up:
			ePos = ePos + Coord(0,1);
			break;
		case Input::Key::A:
		case Input::Key::Left:
			ePos = ePos + Coord(-1,0);
			break;
		case Input::Key::S:
		case Input::Key::Down:
			ePos = ePos + Coord(0,-1);
			break;
		case Input::Key::D:
		case Input::Key::Right:
			ePos = ePos + Coord(1,0);
			break;
	};

	target->move(ePos);
};

Action MoveAction = aMove;

const std::unordered_map<int, Action> DefaultMap = {
	{Input::Key::W, MoveAction},
	{Input::Key::A, MoveAction},
	{Input::Key::S, MoveAction},
	{Input::Key::D, MoveAction},
	{Input::Key::Up, MoveAction},
	{Input::Key::Left, MoveAction},
	{Input::Key::Down, MoveAction},
	{Input::Key::Right, MoveAction}
};

int Input::getInput() {
	if(!kbhit()) return 0;
	int kb_code = getch();

	if(kb_code == 224) {
		kb_code <<= 8;
		kb_code |= getch();
	};

	return kb_code;
};

const Action Input::getAction(int input) const {
	return this->ActionMap.at(input);
};

void Input::callAction(Entity *target, int input) const {
	Action a = this->ActionMap.at(input);
	a(target, input);
};

void Input::addActionMapping(int input, Action action) {
	this->ActionMap[input] = action;
};

void Input::removeActionMapping(int input) {
	this->ActionMap.erase(input);
};

