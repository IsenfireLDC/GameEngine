/*
 * pos.hpp
 *
 * Contains Coord datatype
 */

#ifndef _POS_HPP_
#define _POS_HPP_

struct Coord {
	int x;
	int y;

	bool operator==(Coord a) {
		return this->x == a.x && this->y == a.y;
	};
};

#endif
