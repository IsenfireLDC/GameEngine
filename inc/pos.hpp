/*
 * pos.hpp
 *
 * Contains Coord datatype
 */

#ifndef _POS_HPP_
#define _POS_HPP_

#include <iostream>
#include <windows.h>

struct Coord {
	short x;
	short y;

	Coord() {
		this->x = 0;
		this->y = 0;
	};

	Coord(short x, short y) {
		this->x = x;
		this->y = y;
	};

	bool operator==(Coord a) {
		return this->x == a.x && this->y == a.y;
	};

	operator COORD() const { return (COORD){this->x, this->y}; };

	friend std::ostream& operator<<(std::ostream &out, const Coord &coord) {
		out << "(" << coord.x << ", " << coord.y << ")";
		return out;
	};
};

Coord operator+(const Coord&, const Coord&);
Coord operator*(const Coord&, const Coord&);


#endif
