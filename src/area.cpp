/*
 * area.cpp
 *
 * Contains classes representing areas
 */

#include "area.hpp"


BoundingBox operator*(const BoundingBox &bb, const short scale) {
	BoundingBox bb_s;
	Coord c_scale{scale, scale};

	bb_s.low = bb.low * c_scale;
	bb_s.high = bb.high * c_scale;

	return bb_s;
};

BoundingBox operator*(const BoundingBox &bb, const Coord &scale) {
	BoundingBox bb_s;

	bb_s.low = bb.low * scale;
	bb_s.high = bb.high * scale;

	return bb_s;
};


/*
 * Default constructor
 */
RectArea::RectArea() : c1(0, 0), c2(0, 0) {};

/*
 * Constructor for RectArea from bounding box corners
 */
RectArea::RectArea(Coord c1, Coord c2) {
		this->c1 = c1;
		this->c2 = c2;
};

/*
 * Returns ordered bounding box
 */
BoundingBox RectArea::getBoundingBox() const {
	BoundingBox bb;

	if(c1.x < c2.x) {
		bb.low.x = c1.x;
		bb.high.x = c2.x;
	} else {
		bb.low.x = c2.x;
		bb.high.x = c1.x;
	};

	if(c1.y < c2.y) {
		bb.low.y = c1.y;
		bb.high.y = c2.y;
	} else {
		bb.low.y = c2.y;
		bb.high.y = c1.y;
	};

	return bb;
};

/*
 * Determenis if this Area contains the given Coord
 *
 * Does not include edges by default
 */
bool RectArea::contains(Coord c, bool edges = false) const {
	int a = this->c1.x - c.x;
	int b = this->c2.x - c.x;
	if(a*b > 0 || (!edges && a*b == 0)) return false;

	a = this->c1.y - c.y;
	b = this->c2.y - c.y;
	return a*b < 0 || (edges && a*b == 0);
};
