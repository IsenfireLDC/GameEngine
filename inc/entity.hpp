/*
 * entity.hpp
 *
 * Used for managing entities
 */

#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <vector>
#include <iostream>

#include "area.hpp"
#include "field.hpp"
#include "pos.hpp"

#include "model.hpp"

/*	Types		*/
class Entity {
public:
	//Constructors
	Entity();
	Entity(Coord);

	//Constants
	const static Coord origin;

	//Setters
	void move(Coord);
	void moveBack();

	void setModel(Model*);

	//Getters
	Coord getPosition() const;

	Model* getModel() const;

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

	Model* model;
};

class EntityManager {
public:
	//Constructors
	EntityManager();
	EntityManager(Field*);

	//Get information
	Entity* getEntityAt(Coord) const;
	std::vector<Entity*> getEntities() const;

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
