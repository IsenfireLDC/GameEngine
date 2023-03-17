/*
 * render.hpp
 *
 * Draws scene and entities on the screen
 */

#ifndef _RENDER_HPP_
#define _RENDER_HPP_

#include "pos.hpp"
#include "area.hpp"

#include <vector>
#include <functional>

/*
 * Interface for renderable objects
 *
 * Supplies necessary getters
 */
//class IModelable {
//public:
//	virtual Model* getModel() const = 0;
//	virtual Coord getPos() const = 0;
//	
//	virtual Coord getLastPos() = 0;
//	virtual bool isDirty() = 0;
//};

enum TermColor : unsigned char {
	BLACK = 0x0,
	BLUE = 0x1,
	GREEN = 0x2,
	ORANGE = 0x3,
	RED = 0x4,
	PURPLE = 0x5,
	CYAN = 0x6,
	GRAY = 0x7,
	DARK_GRAY = 0x8,
	LIGHT_BLUE = 0x9,
	LIME = 0xa,
	YELLOW = 0xb,
	BRIGHT_RED = 0xc,
	MAGENTA = 0xd,
	BRIGHT_CYAN = 0xe,
	WHITE = 0xf,
	BG_BLACK = 0x00,
	BG_BLUE = 0x10,
	BG_GREEN = 0x20,
	BG_ORANGE = 0x30,
	BG_RED = 0x40,
	BG_PURPLE = 0x50,
	BG_CYAN = 0x60,
	BG_GRAY = 0x70,
	BG_DARK_GRAY = 0x80,
	BG_LIGHT_BLUE = 0x90,
	BG_LIME = 0xa0,
	BG_YELLOW = 0xb0,
	BG_BRIGHT_RED = 0xc0,
	BG_MAGENTA = 0xd0,
	BG_BRIGHT_CYAN = 0xe0,
	BG_WHITE = 0xf0
};


/*
 * Interface for classes that handle rendering
 */
class Renderer {
public:
	//Rendering helper methods
	static void setCursorPos(Coord);
	static Coord getCursorPos();

	static void setTermColor(unsigned char);
	static void resetTermColor();

public:
	virtual void draw() const = 0;
	virtual void redraw() const = 0;
	virtual void clear() const = 0;

	virtual void setBackground(std::function<void(BoundingBox)>);

protected:
	std::function<void(BoundingBox)> bgFunc;
};

#endif
