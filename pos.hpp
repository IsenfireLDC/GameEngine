/*
 * pos.hpp
 *
 * Contains Coord datatype
 */

#ifndef _POS_HPP_
#define _POS_HPP_

#include <iostream>

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

#endif
