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

class Scene {
public:
	Scene();
	Scene(Field*);
	Scene(Field*, Coord*);

	Field* getField() const;
	Coord* getBorder() const;

	void setField(Field*);
	void setBorder(Coord*, int);

private:
	Field* field;
	Coord* border;
	EntityManager entities;

	char mBorder;
	char mBackground;
	char mOutOfBounds;
};

#endif
