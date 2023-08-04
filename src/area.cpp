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

BoundingBox operator+(const BoundingBox &bb, const Coord &translate) {
	BoundingBox bb_s;

	bb_s.low = bb.low + translate;
	bb_s.high = bb.high + translate;

	return bb_s;
};


/*
 * Default constructor
 */
RectArea::RectArea() : size(0, 0) {};

/*
 * Constructor for RectArea from bounding box corners
 */
RectArea::RectArea(const Coord *origin, Coord size) {
	this->origin = origin;
	this->size = size;
};

RectArea::RectArea(const Coord *origin, float w, float h) {
	this->origin = origin;
	this->size = Coord(w, h);
};

/*
 * Returns ordered bounding box
 */
BoundingBox RectArea::getBoundingBox() const {
	BoundingBox bb = {
		.low = *this->origin,
		.high = *this->origin + this->size
	};

	return bb;
};

/*
 * Determenis if this Area contains the given Coord
 *
 * Does not include edges by default
 */
bool RectArea::contains(Coord c, bool edges = false) const {
	int a = this->origin->x - c.x;
	int b = this->origin->x + this->size.x - c.x;
	if(a*b > 0 || (!edges && a*b == 0)) return false;

	a = this->origin->y - c.y;
	b = this->origin->y + this->size.y - c.y;
	return a*b < 0 || (edges && a*b == 0);
};




bool RectArea::overlaps(const RectArea *other) const {
	return
		this->origin->x + this->size.x >= other->origin->x &&
		this->origin->x <= other->origin->x + other->size.x &&
		this->origin->y + this->size.y >= other->origin->y &&
		this->origin->y <= other->origin->y + other->size.y;
};
