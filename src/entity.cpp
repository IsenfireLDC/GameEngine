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
	this->pos = Entity::origin;
};

/*
 * Constructor for new entity with default collision
 *
 * Coord pos		: Position struct for new entity
 */
Entity::Entity(Coord pos) {
	this->pos = pos;
};

const Coord Entity::origin = Coord(1,1);

/*
 * Moves entity, checking for collision if registered to manager
 */
bool Entity::move(Coord pos) {
	if(this->manager && !this->manager->canPlaceAt(pos)) return false;

	this->pos = pos;

	return true;
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
	return this->pos;
};

/*
 * Getter for model
 */
Model* Entity::getModel() const {
	return this->model;
};



/****	     EntityManager	****/

/*
 * Constructor for default entity manager
 */
EntityManager::EntityManager() {
	this->field = nullptr;
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
 * Destructor
 *
 * Unregisters all entities
 */
EntityManager::~EntityManager() {
	for(int i = this->entities.size()-1; i >= 0; --i)
		this->unregisterEntity(this->entities[i]);
};

/*
 * Finds first entity at given coordinates (1 max at coords)
 *
 * Returns null pointer if no entity found
 */
Entity* EntityManager::getEntityAt(Coord pos) const {
	for(Entity* entity : this->entities)
		if(pos == entity->pos)
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
bool EntityManager::registerEntity(Entity* entity) {
	if(entity == nullptr || !this->canPlaceAt(entity->pos)) return false;

	this->entities.push_back(entity);

	entity->manager = this;

	return true;
};

/*
 * Remove an entity from the entity manager
 *
 * Returns false if entity was null or not found
 */
bool EntityManager::unregisterEntity(Entity* entity) {
	if(entity == nullptr) return false;

	unsigned int index = this->findEntity(entity);
	if(index == this->entities.size()) return false;

	this->entities.erase(this->entities.begin() + index);

	entity->manager = nullptr;

	return true;
};

/*
 * Attempt to move an entity to a new coordinate
 *
 * Returns false if entity is null, else returns move(pos)
 */
bool EntityManager::moveEntity(Entity* entity, Coord pos) {
	if(entity == nullptr) return false;

	//Call entity's move method
	return entity->move(pos);
};

/*
 * Determines if an entity exists at a given location
 */
bool EntityManager::canPlaceAt(Coord pos) const {
	if(this->field && !this->field->contains(pos)) return false;

	for(Entity* entity : this->entities)
		if(pos == entity->pos)
			return false;

	return true;
};

/*
 * Determines where entity exists, size if it does not
 */
unsigned int EntityManager::findEntity(Entity *entity) const {
	for(unsigned int i = 0; i < this->entities.size(); ++i)
		if(this->entities[i] == entity) return i;

	return this->entities.size();
};
