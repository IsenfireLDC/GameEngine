/*
 * Holds the instance object that initializes SDL
 */
#include "log.hpp"

#include <SDL2/SDL.h>

#include "engine.hpp"

//Global
Engine::Instance __attribute__((init_priority(155))) Engine::instance{};

//Static member
bool Engine::Instance::initialized = false;

/*
 * Initialize SDL on startup
 */
Engine::Instance::Instance() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		Engine::log.log("Failed to initialize SDL", LogLevel::Fatal);
		Instance::initialized = false;

		//TODO: Exit?
	} else {
		Engine::log.log("Started SDL", LogLevel::Info);
		Instance::initialized = true;
	};
};

Engine::Instance::~Instance() {
	SDL_Quit();
};
