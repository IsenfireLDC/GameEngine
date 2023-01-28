/*
 * model.cpp
 *
 * Implements helper methods and basic model
 */

#include "model.hpp"

#include <iostream>

#include <windows.h>

/*
 * Constructor
 *
 * Sets the color of the model
 */
Model::Model(TermColor color) {
	this->color = color;
};

/*
 * Clears an area to space and default color
 */
void Model::clear() const {
	Rect rect = this->getBoundingBox().getRect();

	for(short i = rect.c1.x; i <= rect.c2.x; ++i) {
		for(short j = rect.c1.y; j <= rect.c2.y; ++j) {
			Model::setCursorPos((Coord){i,j});
			Model::resetTermColor();
			std::cout << " ";
		};
	};
};

/*
 * Sets the position of the cursor to pos
 */
void Model::setCursorPos(Coord pos) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD)pos);
};

/*
 * Sets the term color to color
 */
void Model::setTermColor(TermColor color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
};

/*
 * Sets the term color to light gray
 */
void Model::resetTermColor() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0b0111);
};


/*
 * Constructor
 *
 * Creates a single colored character
 */
BasicModel::BasicModel(char model, TermColor color) : Model(color) {
	this->model = model;
};

/*
 * Draws the model
 *
 * Sets terminal color and prints character to display
 */
void BasicModel::draw(Coord pos) const {
	Model::setTermColor(model->color);
	std::cout << model->model;
};

/*
 * Get bounding box
 *
 * Will always be a single character (0 x 0)
 */
Area BasicModel::getBoundingBox() const {
	return Area();
};


/*
 * Print the character for the model
 */
std::ostream& operator<<(std::ostream &out, const BasicModel &model) {
	out << model.model;
	return out;
};


/*
 * Constructor
 *
 * Model for a field, draws the outline
 */
FieldModel::FieldModel(const Field &field, const BasicModel &border, const BasicModel &background) : Model(0) {
	this->field = field;
	this->border = border;
	this->background = background;
};

/*
 * Draw the outline of the field
 */
void FieldModel::draw(Coord pos) const {
	Model::resetTermColor();

	Coord size = this->field.getArea()->getRect().c2;
	size = size * this->field.getScale();

	for(short i = 0; i <= size.x; ++i) {
		for(short j = 0; j <= size.y; ++j) {
			Coord currentPos = { .x=i, .y=j };
			Model::setCursorPos(currentPos);

			if(i == 0 || i == size.x || j == 0 || j == size.y) {
				this->border.draw(currentPos);
			} else {
				this->background.draw(currentPos);
			};
		};
	};
};

/*
 * Get the bounds of the field
 */
Area FieldModel::getBoundingBox() const {
	return this->field.getArea();
};
