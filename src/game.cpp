/*
 * game.cpp
 */

#include "game.hpp"

#include "engine.hpp"

/*
 * Creates game with empty tickables set at 30 fps
 */
Game::Game() : tickHandler(&Engine::threadPool) {
	this->setFPS(30);
};

Game::~Game() {
	this->run(false);
};

/*
 * Sets the framerate
 *
 * To set a more exact period, access the TickHandler directly
 */
void Game::setFPS(int fps) {
	this->tickHandler.setTickRate(fps);
};

/*
 * Gets the framerate set by setFPS
 */
int Game::getFPS() const {
	return this->tickHandler.getTickRate();
};

/*
 * Registers the given object with the tick handler
 */
void Game::add(ITick *object) {
	this->tickHandler.registerITick(object);
};

/*
 * Unregisters the given object with the tick handler
 */
void Game::remove(ITick *object) {
	this->tickHandler.unregisterITick(object);
};

/*
 * Starts or stops ticking game objects
 */
void Game::run(bool run) {
	if(run & !this->tickHandler.active())
		this->tickHandler.start();
	else if(!run)
		this->tickHandler.join();
};

/*
 * Grants access to the internal TickHandler
 */
TickHandler* Game::handler() {
	return &this->tickHandler;
};
