/*
 * area.hpp
 *
 * Contains classes representing areas
 */

#ifndef _AREA_HPP_
#define _AREA_HPP_

#include "pos.hpp"


struct BoundingBox {
	Vector2D low;
	Vector2D high;
};

BoundingBox operator*(const BoundingBox&, const short);
BoundingBox operator*(const BoundingBox&, const Vector2D&);
BoundingBox operator+(const BoundingBox&, const Vector2D&);

class Area {
public:
	virtual BoundingBox getBoundingBox() const = 0;
	virtual bool contains(Vector2D, bool = false) const = 0;
};

class RectArea : public Area {
public:
	RectArea();
	RectArea(const Vector2D*, Vector2D);
	RectArea(const Vector2D*, float, float);

	BoundingBox getBoundingBox() const;
	bool contains(Vector2D, bool) const;

	bool overlaps(const RectArea*) const;

protected:
	const Vector2D *origin;
	Vector2D size;
};

#endif
