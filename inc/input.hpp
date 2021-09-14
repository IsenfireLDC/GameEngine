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
//typedef void(*Action)(Entity*, int);

extern Action MoveAction;

extern const std::unordered_map<int, Action> DefaultMap;

//Special key code
const int sKey = (224<<8);

class Input {
public:
	enum Key : int;

	const Action getAction(int) const;
	void callAction(Entity*, int) const;

	void addActionMapping(int, Action);
	void removeActionMapping(int);
private:
	std::unordered_map<int, Action> ActionMap;
};

#endif
