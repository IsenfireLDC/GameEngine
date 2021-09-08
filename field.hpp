/*
 * field.hpp
 *
 * Contains game field information
 */

#ifndef _FIELD_HPP_
#define _FIELD_HPP_

#include "pos.hpp"

class Field {
public:
	//Exposed Constants
	static const int defaultXScale = 2;
	static const int defaultYScale = 1;
	static const Rect defaultArea;

	//Constructors
	Field();
	Field(Rect*, int);
	Field(Rect*, int, int, int);

	//Getters
	int getXScale() const;
	int getYScale() const;

	//Setters
	void setXScale(int);
	void setYScale(int);

	//Queries
	bool isInBounds(Coord) const;

private:
	Rect *area;
	int nRect;

	int xScale;
	int yScale;
};

#endif
