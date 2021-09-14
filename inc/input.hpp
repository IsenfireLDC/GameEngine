/*
 * input.hpp
 *
 * Controls input
 */

#ifndef _INPUT_HPP_
#define _INPUT_HPP_

#include "entity.hpp"

#include <functional>
#include <unordered_map>

typedef std::function<void(Entity*, int)> Action;

extern const Action MoveAction;

extern std::unordered_map<int, const Action> ActionMap;

//Special key code
const int sKey = (224<<8);

enum Inputs : int {
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	Up = sKey|72,
	Left = sKey|75,
	Down = sKey|80,
	Right = sKey|77
};

#endif
