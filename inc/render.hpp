/*
 * render.hpp
 *
 * Draws scene and entities on the screen
 */

#ifndef _RENDER_HPP_
#define _RENDER_HPP_

#include "field.hpp"
#include "pos.hpp"

#include "model.hpp"

#include <vector>

/*
 * Interface for renderable objects
 *
 * Supplies necessary getters
 */
class IModelable {
public:
	virtual Model* getModel() const = 0;
	virtual Coord getPos() const = 0;
	
	virtual Coord getLastPos() = 0;
	virtual bool isDirty() = 0;
};

/*
 * Handles drawing output and passing back input
 */
class Window {
public:
	//Constructors
	Window();
	Window(Field*, const std::vector<IModelable*>*);

	//Getters
	Field* getField() const;

	//Setters
	void setField(Field*);
	void setMsg(const char*);

	//Rendering
	void render();
	void render(bool) const;

private:
	Field *field;
	const std::vector<IModelable*> *modelableList;

	Model *mBorder = new Model('#', 0b1111);
	Model *mBackground = new Model(' ', 0b0000);

	const char * msg = nullptr;

	bool firstRender = true;
};

#endif
