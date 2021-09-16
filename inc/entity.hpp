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

struct EntityData {
	char id;
	char type;
	const char* name;
};

class Entity {
public:
	friend class EntityManager;

	//Static methods
	static char nextID();

	//Constants
	const static Coord origin;
	const static char dName[];

	//Constructors
	Entity();
	Entity(Coord);
	Entity(Coord, char, const char*);

	//Setters
	void setModel(Model*);
	void setData(EntityData);

	//Getters
	Coord getPos() const;
	Model* getModel() const;
	EntityData getData() const;

	//Action
	bool move(Coord);

	bool moveInto(Entity*);


	friend std::ostream& operator<<(std::ostream& out, const Entity& entity) {
		out << entity.data.name;
		if(entity.model) out << "(" << *entity.model << ")";
		out << " type=" << (int)entity.data.type;
		out << " at" << entity.pos;
		if(entity.manager) out << " managed by " << entity.manager;
		return out;
	};

private:
	static char gID;

	Coord pos;

	Model* model;

	EntityData data;

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
