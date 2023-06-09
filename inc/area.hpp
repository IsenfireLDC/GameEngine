/*
 * area.hpp
 *
 * Contains classes representing areas
 */

#ifndef _AREA_HPP_
#define _AREA_HPP_

#include "pos.hpp"


struct BoundingBox {
	Coord low;
	Coord high;
};

BoundingBox operator*(const BoundingBox&, const short);
BoundingBox operator*(const BoundingBox&, const Coord&);
BoundingBox operator+(const BoundingBox&, const Coord&);

class Area {
public:
	virtual BoundingBox getBoundingBox() const = 0;
	virtual bool contains(Coord, bool = false) const = 0;
};

class RectArea : public Area {
public:
	RectArea();
	RectArea(Coord, Coord);

	BoundingBox getBoundingBox() const;
	bool contains(Coord, bool) const;

private:
	Coord c1;
	Coord c2;
};

#endif
