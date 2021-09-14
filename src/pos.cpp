/*
 * pos.cpp
 *
 * Contains Coord datatype
 */

#include "pos.hpp"


Coord operator+(const Coord& c1, const Coord& c2) {
	return Coord(c1.x+c2.x, c1.y+c2.y);
};

Coord operator*(const Coord& c1, const Coord& c2) {
	return Coord(c1.x*c2.x, c1.y*c2.y);
};
