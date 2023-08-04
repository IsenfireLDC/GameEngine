/*
 * field.cpp
 *
 * Contains game field information
 */

#include "field.hpp"

#include "pos.hpp"

const RectArea Field::defaultArea = RectArea();
const Coord Field::defaultScale = Coord(2,1);

/*
 * Constructor for default field
 */
Field::Field() : area(Field::defaultArea) {
	//this->area = Field::defaultArea;
	this->scale = Field::defaultScale;
};

/*
 * Constructor
 * Create a field with given area
 *
 * area - area of the field
 */
Field::Field(Area &area) : area(area) {
	//this->area = area;

	this->scale = Field::defaultScale;
};

/*
 * Constructor
 * Create a field with given area and scale
 *
 * area - field area
 * scale - x and y scale of field
 */
Field::Field(Area &area, Coord scale) : area(area) {
	//this->area = area;

	this->scale = scale;
};


/*
 * Get the bounding box of the field
 */
BoundingBox Field::getBoundingBox() const {
	return this->area.getBoundingBox();
};

/*
 * Getter for scale
 */
Coord Field::getScale() const {
	return this->scale;
};

/*
 * Setter for scale
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
	return pos * this->scale;
};
