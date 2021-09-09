/*
 * field.cpp
 *
 * Contains game field information
 */

#include "field.hpp"

#include "pos.hpp"

const Rect Field::defaultArea = Rect(Coord(1,1), Coord(51,21));

/*
 * Constructor for default field
 */
Field::Field() {
	this->area = new Rect[1];
	*this->area = Field::defaultArea;
	this->nRect = 1;

	this->xScale = Field::defaultXScale;
	this->yScale = Field::defaultYScale;
};

/*
 * Constructor for new field with default scale
 */
Field::Field(Rect *area, int nRect) {
	this->area = area;
	this->nRect = nRect;

	this->xScale = Field::defaultXScale;
	this->yScale = Field::defaultYScale;
};

/*
 * Constructor for new field
 */
Field::Field(Rect *area, int nRect, int xScale, int yScale) {
	this->area = area;
	this->nRect = nRect;

	this->xScale = xScale;
	this->yScale = yScale;
};

/*
 * Getter for xScale
 */
int Field::getXScale() const {
	return this->xScale;
};

/*
 * Getter for yScale
 */
int Field::getYScale() const {
	return this->yScale;
};

/*
 * Setter for xScale
 */
void Field::setXScale(int xScale) {
	this->xScale = xScale;
};

/*
 * Setter for yScale
 */
void Field::setYScale(int yScale) {
	this->yScale = yScale;
};

/*
 * Determines if the given coordinates are out of bounds for this field
 */
bool Field::isInBounds(Coord pos) const {
	for(int i = 0; i < this->nRect; ++i)
		if(area[i].contains(pos)) return true;

	return false;
};
