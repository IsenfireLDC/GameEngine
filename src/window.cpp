/*
 * window.cpp
 *
 * Holds scene and entities; renders the screen
 */

#include "window.hpp"

#include "render.hpp"
#include "model.hpp"

#include "level.hpp"
#include "entity.hpp"
#include "log.hpp"

#include "engine.hpp"

Level *Window::defaultLevel = &Engine::level;
std::string Window::defaultName = "Game Engine 0.1";

Window Engine::window{};

Window::Window(Level *level, std::string name, Coord scale) {
	this->level = level;
	this->scale = scale;

	if(!Engine::instance.good()) {
		Engine::log.log("SDL not initialized", LogLevel::Fatal, "Window");
		return;
	};

	this->window = SDL_CreateWindow(
		name.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 480,
		0
	);

	if(!this->window) {
		Engine::log.log("Failed to create window", LogLevel::Error, "Window");
		return;
	};

	this->renderer = SDL_CreateRenderer(this->window, -1, 0);

	if(!this->renderer) {
		Engine::log.log("Failed to create renderer", LogLevel::Error, "Window");
		return;
	};

	Engine::log.log("Created window", LogLevel::Debug, "Window");
};

Window::~Window() {
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
};


/*
 * Get window size
 */
Coord Window::size() const {
	SDL_Point size;

	SDL_GetWindowSize(this->window, &size.x, &size.y);

	return Coord(size.x, size.y);
};

/*
 * Get window scale
 */
Coord Window::getScale() const {
	return this->scale;
};

/*
 * Get SDL Window
 */
SDL_Window* Window::getWindow() const {
	return this->window;
};

/*
 * Get SDL Renderer
 */
SDL_Renderer* Window::getRenderer() const {
	return this->renderer;
};


/*
 * Changes the size of the window
 *
 * Takes Coord with new width and height
 */
void Window::resize(Coord size) {
	SDL_SetWindowSize(this->window, (int)size.x, (int)size.y);
};

/*
 * Changes the scaling of the window
 */
void Window::setScale(Coord scale) {
	this->scale = scale;
};


/*
 * Draw entire window
 *
 * TODO: Create a camera class for this
 * TODO: Draw by layer
 */
void Window::draw() const {
	if(!this->visible) return;

	Engine::log.log("Drawing window", LogLevel::Info, "Window");

	//Clear the screen
	SDL_RenderClear(this->renderer);

	//Draw the background
	//this->drawBackground(this->windowBB);

	//Draw all entities with a model
	for(Entity *entity : this->level->findEntitiesWithComponent<ModelComponent>()) {
		//TODO: Add culling for offscreen entities
		Model *m = entity->getComponent<ModelComponent>()->getModel();
		Coord pos = entity->pos - m->getOrigin();

		SDL_Texture *tex = m->getTexture()->getTexture();

		SDL_Rect to = {.x=(int)pos.x, .y=(int)pos.y};
		SDL_QueryTexture(tex, 0, 0, &to.w, &to.h);

		//TODO: Add better scaling
		to *= this->scale;

		SDL_RenderCopy(this->renderer, tex, 0, &to);
	};

	SDL_RenderPresent(this->renderer);
};

/*
 * Clear the window
 */
void Window::clear() const {
	SDL_RenderClear(this->renderer);
};


/*
 * Sets whether the window is shown
 */
void Window::show(bool visible) {
	if(visible)
		SDL_ShowWindow(this->window);
	else
		SDL_HideWindow(this->window);

	this->visible = visible;
};
