#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include "render.hpp"
#include "pos.hpp"

#include <unordered_set>
#include <string>

/*
 * Represents a drawable window
 *
 * Handles drawing output and passing back input
 */
class Window {
private:
	static class Level *defaultLevel;
	static std::string defaultName;

public:
	Window(class Level* = Window::defaultLevel, std::string = Window::defaultName, Coord = Coord(1,1));
	~Window();

	//Getters
	Coord size() const;
	Coord getScale() const;

	SDL_Window* getWindow() const;
	SDL_Renderer* getRenderer() const;

	//Setters
	void resize(Coord);
	void setScale(Coord);

	//Rendering
	void draw() const;
	void clear() const;

	void show(bool);

private:
	SDL_Window *window;
	SDL_Renderer *renderer;

	Coord scale;

	bool visible;

	class Level *level;

	const char * msg = nullptr;
};

#endif
