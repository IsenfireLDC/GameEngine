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
	this->curr = Entity::origin;
	this->prev = Entity::origin;
};

/*
 * Constructor for new entity with default collision
 *
 * Coord pos		: Position struct for new entity
 */
Entity::Entity(Coord pos) {
	this->curr = pos;
	this->prev = pos;
};

const Coord Entity::origin = Coord(1,1);

/*
 * Setter for entity position
 */
void Entity::move(Coord pos) {
	this->prev = this->curr;
	this->curr = pos;
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
 * Getter for entity position
 */
Coord Entity::getPos() const {
	return this->curr;
};

/*
 * Getter for model
 */
Model* Entity::getModel() const {
	return this->model;
};

/*
 * Coord collision query
 */
bool Entity::collidesWith(Coord c) {
	return this->curr == c;
};

/*
 * Entity collision query
 */
bool Entity::collidesWith(const Entity* entity) {
	return this->curr == entity->getPos();
};



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
		if(pos == entity->getPos())
			return entity;

	return nullptr;
};

/*
 * Get const pointer to array containing all entities
 */
std::vector<Entity*> EntityManager::getEntities() const {
	return this->entities;
};

/*
 * Add an entity to the entity manager
 *
 * Returns false if an entity already exists in the same location
 */
bool EntityManager::addEntity(Entity* entity) {
	if(entity == nullptr || this->canPlaceAt(entity->getPos())) return false;

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
	if(!this->field->contains(pos)) return false;

	for(Entity* entity : this->entities)
		if(pos == entity->getPos())
			return true;

	return false;
};
