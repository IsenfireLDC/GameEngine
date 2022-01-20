/*
 * game.hpp
 */

#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <unordered_set>

struct ITickable {
	virtual void tick() = 0;
};

class Game {
public:
	Game();

	void setFramePeriod(int);
	int getFramePeriod();

	void registerTickable(ITickable*);
	void unregisterTickable(ITickable*);

	int run();
private:
	int framePeriod;
	
	std::unordered_set<ITickable*> tickables;
};

#endif
