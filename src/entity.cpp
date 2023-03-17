/*
 * entity.cpp
 *
 * Used for managing entities
 */

#include "entity.hpp"

#include "utils.hpp"

#include "log.hpp"

#include <iostream>

#include "engine.hpp"


/****	        Entity     	****/

int Entity::gID = 0;

const Coord Entity::origin = Coord(1,1);
const char Entity::dName[] = "Entity";
const BasicModel Entity::defaultModel{'x', TermColor::BLACK | TermColor::BG_RED};

/*
 * Constructor for new entity
 *
 * Coord pos		: Position struct
 * char type		: Type id
 * const char *name	: Entity name
 */
Entity::Entity(Coord pos, EntityType *type, const char *name, const Model *model) : ModelRenderer(model) {
	this->pos = pos;
	this->lastPos = pos;

	this->type = type;
	this->data = {Utils::nextID(&Entity::gID), 0, name};

	this->ModelRenderer::move(pos);
};

/*
 * Moves entity, checking for collision if registered to manager
 */
bool Entity::move(Coord pos) {
	Engine::log.log("Attempting to move entity");

	//Check if entity at pos
	Entity* other = nullptr;
	if(this->manager) {
		if(!this->manager->inBounds(pos)) return false;
		other = this->manager->getEntityAt(pos);
	};

	//Interact with entity
	bool move = this->moveInto(other);

	//Move entity
	if(move) {
		Engine::log.log("Moving entity");
		this->ModelRenderer::move(pos);
		this->pos = pos;
	};

	this->dirty = move;

	return move;
};

/*
 * Setter for entity data
 */
void Entity::setData(EntityData data) {
	this->dirty = true;
	this->data = data;
};

/*
 * Getter for entity position
 */
Coord Entity::getPos() const {
	return this->pos;
};

/*
 * Getter for last entity position
 */
Coord Entity::getLastPos() {
	Coord lastPos = this->lastPos;
	this->lastPos = this->pos;

	return lastPos;
};

/*
 * Getter for data
 */
EntityData Entity::getData() const {
	return this->data;
};

/*
 * Controls interaction from moving into other entities
 */
bool Entity::moveInto(Entity *other) {
	this->dirty = true;
	if(!other) return true;

	return false;
};

/*
 * Determines if the entity has changed since the last call
 */
bool Entity::isDirty() {
	bool changed = this->dirty;

	this->dirty = false;

	return changed;
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
 * Draw all managed entities
 */
void EntityManager::draw() const {
	for(Entity *entity : this->entities) {
		entity->draw();
	};
};

/*
 * Redraw all managed entities
 */
void EntityManager::redraw() const {
	for(Entity *entity : this->entities) {
		entity->redraw();
	};
};

/*
 * Allows the regions to be cleared
 */
void EntityManager::clear() const {
	for(Entity *entity : this->entities) {
		entity->clear();
	};
};

/*
 * [Override]
 * Sets the background function for every entity managed
 */
void EntityManager::setBackground(std::function<void(BoundingBox)> bgFunc) {
	//Currently unnecessary
	this->Renderer::setBackground(bgFunc);

	for(Entity *entity : this->entities) {
		entity->setBackground(bgFunc);
	};
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
 * Get copy of vector containing all entities
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
 * Determines if coordinate is in field bounds
 */
bool EntityManager::inBounds(Coord pos) const {
	if(this->field) return this->field->contains(pos);

	return false;
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
