/*
 * entity.hpp
 *
 * Used for managing entities
 */

#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <vector>

#include "field.hpp"
#include "pos.hpp"

/*	Types		*/
enum class EntityType {
	Error,
	None,
	Controllable,
	NPC,
	Barrier
};

class Entity {
public:
	//Constructors
	Entity();
	Entity(EntityType, Coord);

	//Constants
	const static Coord origin;

	//Setters
	void setType(EntityType);
	void move(Coord);
	void moveBack();

	//Getters
	EntityType getType() const;
	Coord getPosition() const;
	Coord getLastPosition() const;

	//Actions
	void onMove();
	void onHit(Entity*);

	//Responses
	void onHitBy(Entity*);

private:
	EntityType type;
	Coord curr;
	Coord prev;
};

class EntityManager {
public:
	//Constructors
	EntityManager();
	EntityManager(Field*);

	//Constants
	const static int defaultListSize = 10;
	const int defaultXSize = 51;
	const int defaultYSize = 21;

	//Get information
	Entity* getEntityAt(Coord) const;

	//Add/remove from list
	bool addEntity(Entity*);

	//Take action
	bool moveEntity(Entity*, Coord);

private:
	bool canPlaceAt(Coord) const;

	Field* field;
	std::vector<Entity*> entities;
};

#endif
