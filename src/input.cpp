/*
 * input.cpp
 *
 * Controls input
 */

#include "input.hpp"

static void aMove(Entity *entity, int input) {
	Coord ePos = entity->getPosition();

	switch (input) {
		case Inputs::W:
		case Inputs::Up:
			ePos = ePos + Coord(0,1);
			break;
		case Inputs::A:
		case Inputs::Left:
			ePos = ePos + Coord(-1,0);
			break;
		case Inputs::S:
		case Inputs::Down:
			ePos = ePos + Coord(0,-1);
			break;
		case Inputs::D:
		case Inputs::Right:
			ePos = ePos + Coord(1,0);
			break;
	};

	entity->move(ePos);
};

const Action MoveAction = aMove;

std::unordered_map<int, const Action> ActionMap = {
	{Inputs::W, MoveAction},
	{Inputs::A, MoveAction},
	{Inputs::S, MoveAction},
	{Inputs::D, MoveAction},
	{Inputs::Up, MoveAction},
	{Inputs::Left, MoveAction},
	{Inputs::Down, MoveAction},
	{Inputs::Right, MoveAction}
};
