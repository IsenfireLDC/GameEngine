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

	Coord operator*(const Coord& c1, const Coord& c2) {
		Coord out = c1;
		out.x *= c2.x;
		out.y *= c2.y;
		return out;
	};

	friend std::ostream& operator<<(std::ostream &out, const Coord &coord) {
		out << "(" << coord.x << ", " << coord.y << ")";
		return out;
	};
};

#endif
