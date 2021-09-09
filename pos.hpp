/*
 * pos.hpp
 *
 * Contains Coord datatype
 */

#ifndef _POS_HPP_
#define _POS_HPP_

#include <iostream>
#include <utility>

struct Coord {
	int x;
	int y;

	Coord() {
		this->x = 0;
		this->y = 0;
	};

	Coord(int x, int y) {
		this->x = x;
		this->y = y;
	};

	bool operator==(Coord a) {
		return this->x == a.x && this->y == a.y;
	};

	friend std::ostream& operator<<(std::ostream &out, const Coord &coord) {
		out << "(" << coord.x << ", " << coord.y << ")";
		return out;
	};
};

struct Area {
	virtual ~Area() {};
	virtual bool contains(Coord c) const = 0;
};

struct Rect : public Area {
	Coord c1;
	Coord c2;

	Rect() {
		this->c1 = Coord();
		this->c2 = Coord();
	};

	Rect(Coord c1, Coord c2) {
		this->c1 = c1;
		this->c2 = c2;
	};

	bool contains(Coord c) const {
		int a = c1.x - c.x;
		int b = c2.x - c.x;
		if(a*b > 0) return false;

		a = c1.y - c.y;
		b = c2.y - c.y;
		return a*b <= 0;
	};
};

struct Collider : public Area {
public:
	int nRects;
	Rect *rects;

	Collider() {
		this->nRects = 0;
		this->rects = nullptr;
	};

	Collider(int nRects) {
		this->nRects = nRects;
		this->rects = new Rect[nRects];
	};

	Collider(int nRects, Rect* rects) {
		this->nRects = nRects;
		this->rects = rects;
	};

	Collider(Rect* rect) {
		this->nRects = 1;
		this->rects = rect;
	};

	/*
	 * Destructor
	 *
	 * Deletes rects array
	 */
	virtual ~Collider() {
		delete rects;
	};

	bool contains(Coord c) const {
		for(int i = 0; i < nRects; ++i)
			if(rects[i].contains(c)) return true;

		return false;
	};

	bool overlaps(Collider *c) const {
		for(int i = 0; i < c->nRects; ++i)
			if(this->overlaps(c->rects[i])) return true;

		return false;
	};

private:
	bool overlaps(Rect r) const {
		for(int i = 0; i < nRects; ++i) {
			Rect t = this->rects[i];
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

		return false;
	};

};

#endif
