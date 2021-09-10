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

	Rect(Coord c1, Coord c2) {
		this->c1 = c1;
		this->c2 = c2;
	};
};

class Area {
public:
	//Constructor
	Area();
	Area(Rect*);

	//Destructor
	virtual ~Area();

	//Queries
	virtual bool contains(Coord) const;

protected:
	Rect *area;
	int nParts = 1;
};

class MultiArea : public Area {
public:
	//Constructors
	MultiArea();
	MultiArea(Rect*, int);
};

class Collider : public Area {
public:
	//Constructors
	Collider();
	Collider(Rect*);
	Collider(Rect*, int);

	//Getter
	const Rect* getRects() const;

	//Queries
	bool collidesWith(const Collider*) const;
};

#endif
