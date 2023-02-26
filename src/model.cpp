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
 * Constructor
 *
 * Attaches a model to this renderer
 */
ModelRenderer::ModelRenderer(const Model &model) : model(model) {
	//this->model = model;
};

/*
 * Draws the model
 */
void ModelRenderer::draw() const {
	this->model.draw(this->pos);

	this->lastPos = this->pos;
};

/*
 * Can be overridden to draw only changes
 *
 * By default draws normally
 */
void ModelRenderer::redraw() const {
	this->draw();

	this->lastPos = this->pos;
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
	return this->pos != this->lastPos;
};

/*
 * Sets the position of this model
 */
void ModelRenderer::move(Coord pos) {
	this->pos = pos;
};


/*
 * Constructor
 *
 * Creates a single colored character
 */
BasicModel::BasicModel(char model, TermColor color) : Model(color), model(model) {
	//this->model = model;
};

/*
 * Draws the model
 *
 * Sets terminal color and prints character to display
 */
void BasicModel::draw(Coord pos) const {
	Renderer::setCursorPos(pos);
	Renderer::setTermColor(this->color);
	std::cout << this->model;
};

/*
 * Get bounding box
 *
 * Will always be a single character (0 x 0)
 */
const BoundingBox BasicModel::getBoundingBox() const {
	return BoundingBox{Coord(), Coord()};
};


/*
 * Print the character for the model
 */
std::ostream& operator<<(std::ostream &out, const BasicModel &model) {
	out << model.model;
	return out;
};
