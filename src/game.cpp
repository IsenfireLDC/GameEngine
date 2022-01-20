/*
 * game.cpp
 */

#include "game.hpp"

Game::Game() {
	this->framePeriod = 100;
	this->tickables = std::unordered_set<ITickable*>();
};

/*
 * Sets frame period (in milliseconds)
 */
void Game::setFramePeriod(int framePeriod) {
	this->framePeriod = framePeriod;
};

/*
 * Gets frame period (in milliseconds)
 */
int Game::getFramePeriod() {
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

int Game::run() {return 0;};
