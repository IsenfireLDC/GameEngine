/*
 * game.cpp
 */

#include "game.hpp"

#include "engine.hpp"

/*
 * Creates game with empty tickables set at 30 fps
 */
Game::Game() {
	this->framePeriod = Engine::FPS(30);
	this->tickables = std::unordered_set<ITickable*>();
};

Game::~Game() {
	this->run(false);
};

/*
 * Sets frame period in Utils::Duration (us)
 */
void Game::setFramePeriod(Engine::Units::Time framePeriod) {
	this->framePeriod = framePeriod;
};

/*
 * Gets frame period in Utils::Duration (us)
 */
Engine::Units::Time Game::getFramePeriod() {
	return this->framePeriod;
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
