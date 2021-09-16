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
class EntityManager;

class Entity {
public:
	friend class EntityManager;

	//Constructors
	Entity();
	Entity(Coord);

	//Constants
	const static Coord origin;

	//Setters
	bool move(Coord);

	void setModel(Model*);

	//Getters
	Coord getPos() const;

	Model* getModel() const;


	friend std::ostream& operator<<(std::ostream& out, const Entity& entity) {
		out << "Entity";
		if(entity.model) out << "(" << entity.model << ")";
		out << " at" << entity.pos;
		if(entity.manager) out << " managed by " << entity.manager;
		return out;
	};

private:
	Coord pos;

	Model* model;

	EntityManager *manager = nullptr;
};

class EntityManager {
public:
	//Constructors
	EntityManager();
	EntityManager(Field*);

	virtual ~EntityManager();

	//Get information
	Entity* getEntityAt(Coord) const;
	std::vector<Entity*> getEntities() const;

	//Add/remove from list
	bool registerEntity(Entity*);
	bool unregisterEntity(Entity*);

	//Take action
	bool moveEntity(Entity*, Coord);

	//Query
	bool canPlaceAt(Coord) const;
	unsigned int findEntity(Entity*) const;

	friend std::ostream& operator<<(std::ostream& out, const EntityManager& manager) {
		out << "EntityManager with ";
		if(manager.field) out << "field(" << manager.field << ")and ";
		unsigned int nEnt = manager.entities.size();
		out << nEnt << " registered entities";
		
		if(nEnt == 0) return out;

		out << "{" << *manager.entities[0];
		for(unsigned int i = 1; i < nEnt; ++i)
			out << ", " << *manager.entities[i];
		out << "}";

		return out;
	};

private:

	Field* field;
	std::vector<Entity*> entities;
};

#endif
