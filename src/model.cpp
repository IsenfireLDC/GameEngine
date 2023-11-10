/*
 * model.cpp
 *
 * Implements helper methods and basic model
 */

#include "model.hpp"


Model::Model(Texture *texture, Vector2D origin) {
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
 * Vector2Dinates are from top left corner
 */
void Model::setOrigin(Vector2D origin) {
	this->origin = origin;
};

/*
 * Returns the origin point for the model
 */
Vector2D Model::getOrigin() const {
	return this->origin;
};
