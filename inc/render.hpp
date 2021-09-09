/*
 * render.hpp
 *
 * Draws scene and entities on the screen
 */

#ifndef _RENDER_HPP_
#define _RENDER_HPP_

#include "field.hpp"
#include "pos.hpp"

#include "entity.hpp"

#include <vector>

/*
 * Handles level and models
 */
class Scene {
public:
	//Constructors
	Scene();
	Scene(Field*);
	Scene(Field*, ModelManager*);

	//Register models
	void registerBorder(Model*);
	void registerBackground(Model*);
	void registerOOB(Model*);

private:
	Field *field;
	ModelManager *models;

	Model *mBorder;
	Model *mBackground;
	Model *mOutOfBounds;
};

/*
 * Handles drawing output and passing back input
 */
class Window {
public:
	//Constructors
	Window();
	Window(Scene*);
	Window(Scene*, EntityManager*);

	//Getters
	Scene* getScene() const;

	//Setters
	void setScene(Scene*);

	//Rendering
	void render(Coord);

private:
	Scene *scene;
	EntityManager *entities;
};

#endif
