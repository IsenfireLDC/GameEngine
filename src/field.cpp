/*
 * field.cpp
 *
 * Contains game field information
 */

#include "field.hpp"

#include "pos.hpp"

const Area Field::defaultArea = Area();

/*
 * Constructor for default field
 */
Field::Field() {
	this->area = &Field::defaultArea;
	this->nRect = 1;

	this->xScale = Field::defaultXScale;
	this->yScale = Field::defaultYScale;
};

/*
 * Constructor for new field with default scale
 */
Field::Field(const Area *area, int nRect) {
	this->area = area;
	this->nRect = nRect;

	this->xScale = Field::defaultXScale;
	this->yScale = Field::defaultYScale;
};

/*
 * Constructor for new field
 */
Field::Field(const Area *area, int nRect, int xScale, int yScale) {
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
bool Field::contains(Coord pos) const {
	return this->area->contains(pos);
};

/*
 * Uses the x and y scales to get the transform of a Coord
 */
Coord Field::transform(Coord pos) const {
	return Coord(pos.x*this->xScale, pos.y*this->yScale);
};
