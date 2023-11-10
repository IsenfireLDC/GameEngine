/*
 * game.hpp
 */

#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "utils.hpp"

#include "update.hpp"

#include "engine_types.hpp"

class Game {
public:
	Game();

	~Game();

	void run(bool);

	//TickHandler* handler();

	//template<typename T>
	//void registerEventHandler(int, std::function<void(T*)>);

private:
	void handler();

	bool running;
	bool joining;

	int fps;

	UpdateController<Update> updateController;
	//TaskScheduler<> scheduler;

	//std::unordered_map<int, EventHandler> handlers;
};

#endif
