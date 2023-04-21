#include "level.hpp"

#include "entity.hpp"

/*
 * Constructor for default entity manager
 */
Level::Level() {
	this->field = nullptr;
	this->entities = std::vector<Entity*>();
};

/*
 * Constructor for new entity manager
 */
Level::Level(Field* field) {
	this->field = field;

	this->field->setScale(Coord(2,1));

	this->entities = std::vector<Entity*>();
};

/*
 * Destructor
 *
 * Unregisters all entities
 */
Level::~Level() {
	for(int i = this->entities.size()-1; i >= 0; --i)
		this->unregisterEntity(this->entities[i]);
};


/*
 * Finds first entity at given coordinates (1 max at coords)
 *
 * Returns null pointer if no entity found
 */
Entity* Level::getEntityAt(Coord pos) const {
	for(Entity* entity : this->entities)
		if(pos == entity->pos)
			return entity;

	return nullptr;
};

/*
 * Get copy of vector containing all entities
 */
std::vector<Entity*> Level::getEntities() const {
	return this->entities;
};

/*
 * Add an entity to the entity manager
 *
 * Returns false if an entity already exists in the same location
 */
bool Level::registerEntity(Entity* entity) {
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
bool Level::unregisterEntity(Entity* entity) {
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
bool Level::moveEntity(Entity* entity, Coord pos) {
	if(entity == nullptr) return false;

	//Call entity's move method
	return entity->move(pos);
};

/*
 * Determines if coordinate is in field bounds
 */
bool Level::inBounds(Coord pos) const {
	if(this->field) return this->field->contains(pos);

	return false;
};

/*
 * Determines if an entity exists at a given location
 */
bool Level::canPlaceAt(Coord pos) const {
	if(this->field && !this->field->contains(pos)) return false;

	for(Entity* entity : this->entities)
		if(pos == entity->pos)
			return false;

	return true;
};

/*
 * Determines where entity exists, size if it does not
 */
unsigned int Level::findEntity(Entity *entity) const {
	for(unsigned int i = 0; i < this->entities.size(); ++i)
		if(this->entities[i] == entity) return i;

	return this->entities.size();
};
