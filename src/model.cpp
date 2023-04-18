/*
 * model.cpp
 *
 * Implements helper methods and basic model
 */

#include "model.hpp"


Model::Model(Texture *texture, Coord origin) {
	this->texture = texture;
	this->origin = origin;
};


/*
 * Assigns a new texture to this model
 */
void Model::setTexture(Texture *texture) {
	this->texture = texture;
};

/*
 * Returns the texture associated with this model
 */
Texture* Model::getTexture() const {
	return this->texture;
};


/*
 * Sets the origin point for the model
 * Coordinates are from top left corner
 */
void Model::setOrigin(Coord origin) {
	this->origin = origin;
};

/*
 * Returns the origin point for the model
 */
Coord Model::getOrigin() const {
	return this->origin;
};



/*
 * Create component with the given model
 */
ModelComponent::ModelComponent(Model *model) {
	this->model = model;
};


/*
 * Attach a new model to the component
 */
void ModelComponent::setModel(Model *model) {
	this->model = model;
};

/*
 * Return the model attached to this component
 */
Model* ModelComponent::getModel() const {
	return this->model;
};
