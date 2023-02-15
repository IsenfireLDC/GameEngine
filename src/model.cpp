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
 * Can be overridden to draws only changes
 *
 * By default draws normally
 */
void ModelRenderer::redraw() const {
	this->changed = false;

	this->draw();
};

/*
 * Clears an area to space and default color
 */
//void Model::clear() const {
//	BoundingBox bb = this->getBoundingBox();
//
//	Renderer::resetTermColor();
//	for(short i = bb.low.x; i <= bb.high.x; ++i) {
//		for(short j = bb.low.y; j <= bb.high.y; ++j) {
//			Renderer::setCursorPos((Coord){i,j});
//			std::cout << " ";
//		};
//	};
//};

/*
 * Returns whether the model has changed since last (re)draw
 */
bool ModelRenderer::dirty() const {
	return this->changed;
};

/*
 * Sets the position of this model
 */
void ModelRenderer::setPos(Coord pos) {
	this->pos = pos;

	this->changed = true;
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
	Renderer::setCursorPos(pos);
	Renderer::setTermColor(model->color);
	std::cout << model->model;
};

/*
 * Get bounding box
 *
 * Will always be a single character (0 x 0)
 */
BoundingBox BasicModel::getBoundingBox() const {
	return BoundingBox{Coord(), Coord()};
};


/*
 * Print the character for the model
 */
std::ostream& operator<<(std::ostream &out, const BasicModel &model) {
	out << model.model;
	return out;
};
