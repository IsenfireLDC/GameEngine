/*
 * area.cpp
 *
 * Contains classes representing areas
 */

#include "area.hpp"

/*
 * Constructor for default Area
 */
Area::Area() {
	this->area = Rect();
};

/*
 * Constructor for new Area
 */
Area::Area(Rect area) {
	this->area = area;
};

/*
 * Getter for rect
 */
Rect Area::getRect() const {
	return this->area;
};

/*
 * Determines if this Area contains the given Coord
 *
 * Does not include edges
 */
bool Area::contains(Coord c) const {
	return this->contains(c, false);
};

/*
 * Determenis if this Area contains the given Coord
 *
 * Includes edges if edges
 */
bool Area::contains(Coord c, bool edges) const {
	int a = this->area.c1.x - c.x;
	int b = this->area.c2.x - c.x;
	if(a*b > 0 || !edges && a*b == 0) return false;

	a = this->area.c1.y - c.y;
	b = this->area.c2.y - c.y;
	return a*b < 0 || edges && a*b == 0;
};
