/*
 * area.cpp
 *
 * Contains classes representing areas
 */

#include "area.hpp"

/******** Area **********/

/*
 * Constructor for default Area
 */
Area::Area() {
	this->area = new Rect();
};

/*
 * Constructor for new Area
 */
Area::Area(Rect *area) {
	this->area = area;
};

/*
 * Destructor for Area
 */
Area::~Area() {
	delete this->area;
};

/*
 * Determines if this Area contains the given Coord
 */
bool Area::contains(Coord c) const {
	for(int i = 0; i < this->nParts; ++i) {
		Rect r = this->area[i];

		int a = r.c1.x - c.x;
		int b = r.c2.x - c.x;
		if(a*b > 0) continue;

		a = r.c1.y - c.y;
		b = r.c2.y - c.y;
		if(a*b <= 0) return true;
	};

	return false;
};


/****** MultiArea *******/

/*
 * Constructor for default MultiArea
 */
MultiArea::MultiArea() : Area() {};

/*
 * Constructor for new MultiArea
 */
MultiArea::MultiArea(Rect *area, int nParts) {
	this->area = area;
	this->nParts = nParts;
};


/******* Collider *******/

/*
 * Constructor for default Collider
 */
Collider::Collider() : Area() {};

/*
 * Constructor for single Rect Collider
 */
Collider::Collider(Rect *area) : Area(area) {};

/*
 * Constructor for multi Rect Collider
 */
Collider::Collider(Rect *area, int nParts) {
	this->area = area;
	this->nParts = nParts;
};

/*
 * Getter for Rect array
 */
const Rect* Collider::getRects(int *nParts) const {
	*nParts = this->nParts;
	return this->area;
};

/*
 * Determines if this and a given Collider are colliding
 */
bool collidesWith(const Collider* other) {
	int nRects;
	Rect *rects = other->getRects(&nRects);

	for(int i = 0; i < nRects; ++i) {
		Rect r = rects[i];
		for(int j = 0; j < this->nParts; ++j) {
			Rect t = this->area[j];
			//Check if x or y of both points on the same side of other rect
			bool x[4], y[4];

			//X relations (vertical sides)
			x[0] = t.c1.x > r.c1.x;
			x[1] = t.c1.x > r.c2.x;
			x[2] = t.c2.x > r.c1.x;
			x[3] = t.c2.x > r.c2.x;
			//Check x relationships
			if(x[0] && x[1] && x[2] && x[3]) continue;
			if(!(x[0] || x[1] || x[2] || x[3])) continue;


			//Y relations (horizontal sides)
			y[0] = t.c1.y > r.c1.y;
			y[1] = t.c1.y > r.c2.y;
			y[2] = t.c2.y > r.c1.y;
			y[3] = t.c2.y > r.c2.y;
			//Check y relationships
			if(y[0] && y[1] && y[2] && y[3]) continue;
			if(!(y[0] || y[1] || y[2] || y[3])) continue;

			return true;
		};
	};

	return false;
};
