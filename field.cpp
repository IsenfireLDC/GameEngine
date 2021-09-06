/*
 * field.cpp
 *
 * Contains game field information
 */

#include "field.hpp"

/*
 * Constructor for default field
 */
Field::Field() {
	this->xSize = Field::defaultXSize;
	this->ySize = Field::defaultYSize;
	this->xScale = Field::defaultXScale;
};

/*
 * Constructor for new field with default xScale
 */
Field::Field(int xSize, int ySize) {
	this->xSize = xSize;
	this->ySize = ySize;

	this->xScale = Field::defaultXScale;
};

/*
 * Constructor for new field
 */
Field::Field(int xSize, int ySize, int xScale) {
	this->xSize = xSize;
	this->ySize = ySize;
	this->xScale = xScale;
};

/*
 * Getter for xSize
 */
int Field::getXSize() const {
	return this->xSize;
};

/*
 * Getter for ySize
 */
int Field::getYSize() const {
	return this->ySize;
};

/*
 * Getter for xScale
 */
int Field::getXScale() const {
	return this->xScale;
};

/*
 * Setter for xSize
 */
void Field::setXSize(int xSize) {
	this->xSize = xSize;
};

/*
 * Setter for ySize
 */
void Field::setYSize(int ySize) {
	this->ySize = ySize;
};

/*
 * Setter for xScale
 */
void Field::setXScale(int xScale) {
	this->xScale = xScale;
};

/*
 * Determines if the given coordinates are out of bounds for this field
 */
bool Field::isOutOfBounds(Coord pos) const {
	//Check lower bound
	if(pos.x < 0 || pos.y < 0) return true;

	//Check upper bound
	if(pos.x * this->xScale > this->xSize || pos.y > this->ySize) return true;

	return false;
};
