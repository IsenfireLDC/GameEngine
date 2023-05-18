#include "level.hpp"

#include "entity.hpp"

#include "engine.hpp"

Level Engine::level{};

/*
 * Create new level
 * Initialize empty set of entities
 */
Level::Level() {};

/*
 * Destructor
 */
Level::~Level() {};


/*
 * Add an entity to the level
 */
void Level::addEntity(Entity *entity) {
	this->entities.insert(entity);
};

/*
 * Remove an entity from the level
 */
void Level::removeEntity(Entity *entity) {
	this->entities.erase(entity);
};


/*
 * Checks if the given entity exists in this level
 */
bool Level::hasEntity(Entity *entity) const {
	return this->entities.count(entity) > 0;
};

/*
 * Finds an entity with the given name
 * TODO: Add other systems to search for a specific Entity*; type/id
 */
Entity* Level::findEntity(std::string name) const {
	for(Entity *entity : this->entities)
		if(entity->name == name)
			return entity;

	return nullptr;
};
