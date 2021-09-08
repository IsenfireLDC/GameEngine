/*
 * entity.cpp
 *
 * Used for managing entities
 */

#include "entity.hpp"

#include <iostream>


/****	     EntityManager	****/

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
 * Setter for entity model
 */
void Entity::setModel(Model *model) {
	this->model = model;
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
 * Getter for model
 */
Model* Entity::getModel() const {
	return this->model;
};

/*
 * Handler for actions on move
 */
void Entity::onMove() {};

/*
 * Handler for hitting another entity
 */
void Entity::onHit(Entity* entity) {};

/*
 * Handler for getting hit
 */
void Entity::onHitBy(Entity* entity) {};



/****	     EntityManager	****/

/*
 * Constructor for default entity manager
 */
EntityManager::EntityManager() {
	this->field = new Field();
	this->entities = std::vector<Entity*>();
};

/*
 * Constructor for new entity manager
 */
EntityManager::EntityManager(Field* field) {
	this->field = field;

	this->entities = std::vector<Entity*>();
};

/*
 * Finds first entity at given coordinates (1 max at coords)
 *
 * Returns null pointer if no entity found
 */
Entity* EntityManager::getEntityAt(Coord pos) const {
	for(Entity* entity : this->entities)
		if(pos == entity->getPosition())
			return entity;

	return nullptr;
};

/*
 * Get const pointer to array containing all entities
 */
Entity *const * EntityManager::getEntities() const {
	return this->entities.data();
};

/*
 * Get size of entities list
 */
int EntityManager::size() const {
	return this->entities.size();
};

/*
 * Add an entity to the entity manager
 *
 * Returns false if an entity already exists in the same location
 */
bool EntityManager::addEntity(Entity* entity) {
	if(entity == nullptr || this->canPlaceAt(entity->getPosition())) return false;

	this->entities.push_back(entity);

	return true;
};

/*
 * Attempt to move an entity to a new coordinate
 *
 * Returns false if an entity is already there
 */
bool EntityManager::moveEntity(Entity* entity, Coord pos) {
	if(entity == nullptr || this->canPlaceAt(pos)) return false;

	//Call entity's move method
	entity->move(pos);

	return true;
};

/*
 * Determines if an entity exists at a given location
 */
bool EntityManager::canPlaceAt(Coord pos) const {
	if(!this->field->isInBounds(pos)) return false;

	for(Entity* entity : this->entities)
		if(pos == entity->getPosition())
			return true;

	return false;
};
