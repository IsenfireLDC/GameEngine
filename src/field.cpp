/*
 * field.cpp
 *
 * Contains game field information
 */

#include "field.hpp"

#include "pos.hpp"

const RectArea Field::defaultArea = RectArea();
const Vector2D Field::defaultScale = Vector2D(2,1);

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
Field::Field(Area &area, Vector2D scale) : area(area) {
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
Vector2D Field::getScale() const {
	return this->scale;
};

/*
 * Setter for scale
 */
void Field::setScale(Vector2D scale) {
	this->scale = scale;
};

/*
 * Determines if the given coordinates are out of bounds for this field
 */
bool Field::contains(Vector2D pos) const {
	return this->area.contains(pos);
};

/*
 * Uses the x and y scales to get the transform of a Vector2D
 */
Vector2D Field::transform(Vector2D pos) const {
	return pos * this->scale;
};
