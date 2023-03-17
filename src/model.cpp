/*
 * model.cpp
 *
 * Implements helper methods and basic model
 */

#include "model.hpp"

#include "log.hpp"

#include <iostream>

#include <windows.h>

#include "engine.hpp"


/*
 * Constructor
 *
 * Creates a single colored character
 */
BasicModel::BasicModel(char model, unsigned char color) : model(model), color(color) {};

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
 * Draws the model
 *
 * Same as BasicModel::draw
 */
void BasicModel::redraw(Coord pos) const {
	this->draw(pos);
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


/*
 * Constructor
 *
 * Attaches a model to this renderer
 */
ModelRenderer::ModelRenderer(const Model *model) : model(model) {
	//this->model = model;
};

/*
 * Returns the model that this renderer will draw
 */
const Model* ModelRenderer::getModel() const {
	return this->model;
};

/*
 * Changes the model that this renderer will draw
 */
void ModelRenderer::setModel(const Model *model) {
	Engine::log.log("Set Model");

	this->changed = this->model != model;

	this->model = model;
};

/*
 * Returns the area that should be cleared before the model is drawn
 */
BoundingBox ModelRenderer::getLastRegion() const {
	return this->model->getBoundingBox() + this->lastPos;
};

/*
 * Draws the model
 */
void ModelRenderer::draw() const {
	Engine::log.log("Drawing model");

	this->model->draw(this->pos);

	this->lastPos = this->pos;
	this->changed = false;
};

/*
 * Draws the model
 */
void ModelRenderer::redraw() const {
	Engine::log.log("Redrawing model");

	if(this->dirty()) this->clear();

	this->model->redraw(this->pos);

	this->lastPos = this->pos;
	this->changed = false;
};

/*
 * Allows the region to be cleared
 */
void ModelRenderer::clear() const {
	this->bgFunc(this->getLastRegion());
};

/*
 * Returns whether the model has changed since last (re)draw
 */
bool ModelRenderer::dirty() const {
	return this->pos != this->lastPos || this->changed;
};

/*
 * Sets the position of this model
 */
void ModelRenderer::move(Coord pos) {
	this->pos = pos;
};
