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
 * Handles drawing output and passing back input
 */
class Window {
public:
	//Constructors
	Window();
	Window(Field*, EntityManager*);

	//Getters
	Field* getField() const;

	//Setters
	void setField(Field*);
	void setMsg(const char*);

	//Rendering
	void render() const;

private:
	Field *field;
	EntityManager *entities;

	Model *mBorder = new Model('#', 0b1111);
	Model *mBackground = new Model(' ', 0b0000);

	const char * msg = nullptr;
};

#endif
