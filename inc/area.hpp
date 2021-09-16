/*
 * area.hpp
 *
 * Contains classes representing areas
 */

#ifndef _AREA_HPP_
#define _AREA_HPP_

#include "pos.hpp"


struct Rect {
	Coord c1;
	Coord c2;

	Rect() {
		this->c1 = Coord(0,0);
		this->c2 = Coord(0,0);
	};

	Rect(Coord c1, Coord c2) {
		this->c1 = c1;
		this->c2 = c2;
	};
};

class Area {
public:
	//Constructor
	Area();
	Area(Rect);

	//Getter
	Rect getRect() const;

	//Queries
	virtual bool contains(Coord) const;
	virtual bool contains(Coord, bool) const;

private:
	Rect area;
};

#endif
