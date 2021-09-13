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
	static const int defaultXScale = 2;
	static const int defaultYScale = 1;
	static const Area defaultArea;

	//Constructors
	Field();
	Field(const Area*);
	Field(Area*, int, int);

	//Getters
	Coord getScale() const;
	Coord getOrigin() const;
	int getXScale() const;
	int getYScale() const;

	//Setters
	void setXScale(int);
	void setYScale(int);

	//Queries
	bool contains(Coord) const;

	//Operations
	Coord transform(Coord) const;

private:
	const Area* a;

	int xScale;
	int yScale;
};

#endif
