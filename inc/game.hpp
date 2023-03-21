/*
 * game.hpp
 */

#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "utils.hpp"
#include "tick.hpp"

#include <chrono>
#include <ratio>
#include <unordered_set>

#include "engine_types.hpp"

class Game {
public:
	Game();

	~Game();

	void setFPS(int);
	int getFPS() const;

	void add(ITick*);
	void remove(ITick*);

	void run(bool);

	TickHandler* handler();

private:
	int fps;
	TickHandler tickHandler;
};

#endif
