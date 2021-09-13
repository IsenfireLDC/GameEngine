/*
 * field.hpp
 *
 * Contains game field information
 */

#ifndef _FIELD_HPP_
#define _FIELD_HPP_

#include "area.hpp"
#include "pos.hpp"


class Field {
public:
	//Exposed Constants
	static const Coord defaultScale;

	//Constructors
	Field();
	Field(Coord);
	Field(Coord, Coord);

	//Getters
	Coord getScale() const;

	//Setters
	void setScale(Coord);

	//Queries
	bool contains(Coord) const;

	//Operations
	Coord transform(Coord) const;

private:
	const Area* a;

	Coord scale;
};

#endif
