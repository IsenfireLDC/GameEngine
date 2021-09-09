/*
 * entity.hpp
 *
 * Used for managing entities
 */

#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <vector>
#include <iostream>

#include "field.hpp"
#include "pos.hpp"

#include "model.hpp"

/*	Types		*/
class Entity {
public:
	//Constructors
	Entity();
	Entity(Coord);
	Entity(Coord, const Collider*);

	//Constants
	const static Coord origin;
	const static Collider *dCollision;

	//Setters
	void move(Coord);
	void moveBack();
	void setCollision(const Collider*);

	void setModel(Model*);

	//Getters
	Coord getPosition() const;
	const Collider* getCollision() const;

	Model* getModel() const;

	//Actions
	void onMove();
	void onHit(Entity*);

	//Responses
	void onHitBy(Entity*);

	//Queries
	bool collidesWith(Coord);
	bool collidesWith(const Entity*);

	friend std::ostream& operator<<(std::ostream& out, const Entity& entity) {
		out << "Entity";
		if(entity.getModel() != nullptr) out << "(" << entity.getModel() << ")";
		out << " at" << entity.curr;
		return out;
	};

private:
	Coord curr;
	Coord prev;

	const Collider *collision;

	Model* model;
};

class EntityManager {
public:
	//Constructors
	EntityManager();
	EntityManager(Field*);

	//Constants
	const int defaultXSize = 51;
	const int defaultYSize = 21;

	//Get information
	Entity* getEntityAt(Coord) const;
	Entity *const * getEntities() const;
	int size() const;

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
