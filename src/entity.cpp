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

const Vector2D Entity::origin = Vector2D(1,1);
const std::string Entity::defaultName = "Entity";
Level *const Entity::defaultLevel = &Engine::level;

Entity *Engine::player = nullptr;

/*
 * Constructor for new entity
 *
 * Vector2D pos		: Position struct
 * char type		: Type id
 * const char *name	: Entity name
 */
Entity::Entity(std::string name, Level *level, Vector2D pos) : Update(level), name(name) {
	level->addEntity(this);
	this->level = level;

	this->pos = pos;

	this->id = Utils::nextID(&Entity::gID);
	this->state = 0;
};


/*
 * Constructor overload with different argument order
 */
Entity::Entity(std::string name, Vector2D pos, Level *level) : Entity(name, level, pos) {};


Entity::~Entity() {
	this->level->removeEntity(this);
};


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
