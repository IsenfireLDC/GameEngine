/*
 * field.cpp
 *
 * Contains game field information
 */

#include "field.hpp"

#include "pos.hpp"

const Coord Field::defaultScale = Coord(2,1);

/*
 * Constructor for default field
 */
Field::Field() {
	this->area = Area()

	this->scale = Field::defaultScale;
};

/*
 * Constructor for new field with default scale
 */
Field::Field(Coord corner) {
	this->area = Area(Coord(0, 0), corner);

	this->scale = Field::defaultScale;
};

/*
 * Constructor for new field
 *
 * Coord corner	: Coord of far corner
 * Coord scale	: Render coord of (1,1)
 */
Field::Field(Coord corner, Coord scale) {
	this->area = Area(Coord(0,0), corner);

	this->scale = scale;
};

/*
 * Getter for scale
 */
Coord Field::getScale() const {
	return this->scale;
};

/*
 * Setter for xScale
 */
void Field::setScale(Coord scale) {
	this->scale = scale;
};

/*
 * Determines if the given coordinates are out of bounds for this field
 */
bool Field::contains(Coord pos) const {
	return this->area.contains(pos);
};

/*
 * Uses the x and y scales to get the transform of a Coord
 */
Coord Field::transform(Coord pos) const {
	return pos * scale;
};
