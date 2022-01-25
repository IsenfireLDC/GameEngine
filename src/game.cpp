/*
 * game.cpp
 */

#include "game.hpp"

Game::Game() {
	this->framePeriod = std::chrono::milliseconds(100);
	this->tickables = std::unordered_set<ITickable*>();
};

/*
 * Sets frame period (in milliseconds)
 */
void Game::setFramePeriod(int framePeriod) {
	this->framePeriod = std::chrono::milliseconds(framePeriod);
};

/*
 * Gets frame period (in milliseconds)
 */
int Game::getFramePeriod() {
	return this->framePeriod.count();
};

/*
 * Adds a ITickable* to the set (a tickable can only be added once)
 */
void Game::registerTickable(ITickable *tickable) {
	this->tickables.insert(tickable);
};

/*
 * Removes a ITickable* from the set
 */
void Game::unregisterTickable(ITickable* tickable) {
	if(this->tickables.count(tickable))
		this->tickables.erase(tickable);
};

int Game::run(bool run) {
	static Utils::CallbackHandle *handler;

	if(run) {
		if(handler) return 0;
		else handler = Utils::scheduleAsyncCallback(this->framePeriod, [this](void* p){this->tick();}, true, false);
	} else if (handler) {
		Utils::destroyAsyncCallback(handler);
		handler = nullptr;
	};

	return 0;
};

void Game::tick() {
	for(ITickable *tickable : this->tickables)
		tickable->tick();
};
