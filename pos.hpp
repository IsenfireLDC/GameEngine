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

	bool operator==(Coord a) {
		return this->x == a.x && this->y == a.y;
	};

	friend std::ostream& operator<<(std::ostream &out, const Coord &coord) {
		out << "(" << coord.x << ", " << coord.y << ")";
		return out;
	};
};

struct Rect {
	Coord c1;
	Coord c2;

	Rect(Coord c1, Coord c2) {
		this->c1 = c1;
		this->c2 = c2;
	};

	bool isInBounds(Coord c) {
		int a = c1.x - c.x;
		int b = c2.x - c.x;
		if(a*b > 0) return false;

		a = c1.y - c.y;
		b = c2.y - c.y;
		return a*b <= 0;
	};
};

#endif
