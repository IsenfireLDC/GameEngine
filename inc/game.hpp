/*
 * game.hpp
 */

#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "utils.hpp"
#include "units.hpp"

#include <chrono>
#include <ratio>
#include <unordered_set>

struct ITickable {
	virtual void tick() = 0;
};

class Game {
public:
	Game();

	~Game();

	void setFramePeriod(Engine::Units::Time);
	Engine::Units::Time getFramePeriod();

	void registerTickable(ITickable*);
	void unregisterTickable(ITickable*);

	int run(bool);
private:
	void tick();

	Engine::Units::Time framePeriod;
	
	std::unordered_set<ITickable*> tickables;
};

namespace Engine {
	template<class duration = Units::Time>
	duration FPS(int fps);
};

#endif
