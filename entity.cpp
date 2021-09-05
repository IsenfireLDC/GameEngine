/*
 * entity.cpp
 *
 * Used for managing entities
 */

#include "entity.hpp"

/*
 * Constructor for default entity (type=None, pos=origin)
 */
Entity::Entity() {
	this->type = EntityType::None;
	this->curr = Entity::origin;
	this->prev = Entity::origin;
};

/*
 * Constructor for new entity
 *
 * EntityType type	: Type enum for new entity
 * Coord pos		: Position struct for new entity
 */
Entity::Entity(EntityType type, Coord pos) {
	this->type = type;
	this->curr = pos;
	this->prev = pos;
};

const Coord Entity::origin = (Coord){1,1};

/*
 * Setter for entity type
 */
void Entity::setType(EntityType type) {
	this->type = type;
};

/*
 * Setter for entity position
 */
void Entity::move(Coord pos) {
	this->prev = this->curr;
	this->curr = pos;

	this->onMove();
};

/*
 * Resets entity position to previous position
 */
void Entity::moveBack() {
	this->curr = this->prev;
};

/*
 * Getter for entity type
 */
EntityType Entity::getType() const {
	return this->type;
};

/*
 * Getter for entity position
 */
Coord Entity::getPosition() const {
	return this->curr;
};

/*
 * Getter for previous entity position
 */
Coord Entity::getLastPosition() const {
	return this->prev;
};

/*
 * Handler for actions on move
 */
void Entity::onMove() {};

/*
 * Handler for hitting another entity
 */
void onHit(Entity* entity) {};

/*
 * Handler for getting hit
 */
void onHitBy(Entity* entity) {};
