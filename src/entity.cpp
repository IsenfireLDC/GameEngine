/*
 * entity.cpp
 *
 * Used for managing entities
 */

#include "entity.hpp"

#include "utils.hpp"
#include "log.hpp"

#include <iostream>

#include "level.hpp"

#include "engine.hpp"


/****	        Entity     	****/

int Entity::gID = 0;

const Coord Entity::origin = Coord(1,1);
const std::string Entity::defaultName = "Entity";
Level *const Entity::defaultLevel = &Engine::level;

Entity *Engine::player = nullptr;

/*
 * Constructor for new entity
 *
 * Coord pos		: Position struct
 * char type		: Type id
 * const char *name	: Entity name
 */
Entity::Entity(std::string name, Level *level, Coord pos) : Update(level), name(name) {
	level->addEntity(this);
	this->level = level;

	this->pos = pos;

	this->id = Utils::nextID(&Entity::gID);
	this->state = 0;
};


/*
 * Constructor overload with different argument order
 */
Entity::Entity(std::string name, Coord pos, Level *level) : Entity(name, level, pos) {};


/*
 * Updates this entity
 */
void Entity::update(float delta) {};


/*
 * Attaches the given component to this entity
 */
void Entity::attachComponent(ComponentBase *component) {
	int componentID = component->componentID();
	if(this->components.count(componentID) == 0) {
		this->components.emplace();
	};

	this->components[componentID].insert(component);
};

/*
 * Detaches the given component from this entity
 */
void Entity::detachComponent(ComponentBase *component) {
	int componentID = component->componentID();
	if(this->components.count(componentID) == 0) return;
	
	if(this->components[componentID].count(component) == 0) return;

	this->components[componentID].erase(component);
};
