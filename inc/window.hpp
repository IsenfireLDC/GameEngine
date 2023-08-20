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
	Window(class Level* = Window::defaultLevel, std::string = Window::defaultName, Vector2D = Vector2D(1,1));
	~Window();

	//Getters
	Vector2D size() const;
	Vector2D getScale() const;

	SDL_Window* getWindow() const;
	SDL_Renderer* getRenderer() const;

	//Setters
	void resize(Vector2D);
	void setScale(Vector2D);

	//Rendering
	void draw() const;
	void clear() const;

	void show(bool);

private:
	SDL_Window *window;
	SDL_Renderer *renderer;

	Vector2D scale;

	bool visible;

	class Level *level;

	const char * msg = nullptr;
};

#endif
