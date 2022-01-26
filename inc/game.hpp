/*
 * game.hpp
 */

#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "utils.hpp"

#include <chrono>
#include <ratio>
#include <unordered_set>

struct ITickable {
	virtual void tick() = 0;
};

class Game {
public:
	Game();

	void setFramePeriod(Utils::Duration);
	Utils::Duration getFramePeriod();

	void registerTickable(ITickable*);
	void unregisterTickable(ITickable*);

	int run(bool);
private:
	void tick();

	Utils::Duration framePeriod;
	
	std::unordered_set<ITickable*> tickables;
};

#endif
