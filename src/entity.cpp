/*
 * entity.cpp
 *
 * Used for managing entities
 */

#include "entity.hpp"

#include "level.hpp"

#include "utils.hpp"
#include "log.hpp"

#include <iostream>

#include "engine.hpp"


/****	        Entity     	****/

int Entity::gID = 0;

const Coord Entity::origin = Coord(1,1);
const std::string Entity::defaultName = "Entity";
Level *const Entity::defaultLevel = &Engine::level;

/*
 * Constructor for new entity
 *
 * Coord pos		: Position struct
 * char type		: Type id
 * const char *name	: Entity name
 */
Entity::Entity(std::string name, Level *level, Coord pos) : Update(level) {
	level->addEntity(this);
	this->level = level;

	this->pos = pos;

	this->id = Utils::nextID(&Entity::gID);
	this->state = 0;
	this->name = name;
};


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
