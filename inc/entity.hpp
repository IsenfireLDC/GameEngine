/*
 * entity.hpp
 *
 * Used for managing entities
 */

#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <vector>
#include <iostream>

#include <functional>
#include <unordered_map>

#include "area.hpp"
#include "field.hpp"
#include "pos.hpp"

#include "model.hpp"

#include "render.hpp"

/*	Types		*/
class EntityManager;
class Entity;

struct EntityData {
	int id;
	int state;
	const char* name;
};

struct EntityAction {
	Entity *sender;
	int id;
	void *data;
};

typedef std::function<int(Entity*, EntityAction)> EntityActionHandler;

//Singleton type
struct EntityType {
	int id;
	const char* name;
	std::unordered_map<int, EntityActionHandler> handlers;

	EntityType(int id, const char *name) {
		this->id = id;
		this->name = name;

		this->handlers = std::unordered_map<int, EntityActionHandler>();
	};
};

class Entity : public ModelRenderer {
public:
	friend class EntityManager;

	//Constants
	const static Coord origin;
	const static char dName[];
	const static BasicModel defaultModel;

	//Constructors
	Entity(Coord=Coord(), EntityType* =nullptr, const char* =Entity::dName, const Model* =&Entity::defaultModel);

	//Setters
	void setModel(Model*);
	void setData(EntityData);

	//Getters
	EntityData getData() const;

	//Action
	int sendAction(Entity*, EntityAction);
	int receiveAction(EntityAction);

	virtual bool move(Coord);

	virtual bool moveInto(Entity*);

	//IModelable interface
	Model* getModel() const;
	Coord getPos() const;
	Coord getLastPos();
	bool isDirty();


	friend std::ostream& operator<<(std::ostream& out, const Entity& entity) {
		out << entity.data.name;
		if(entity.model && &out == &std::cout) {
			out << "(";
			entity.model->draw(Renderer::getCursorPos());
			out << ")";
		};
		out << " id=" << (int)entity.data.id;
		out << " type=" << (int)entity.type->id;
		out << " at" << entity.pos;
		if(entity.manager) out << " managed by " << entity.manager;
		return out;
	};

private:
	static int gID;

	Coord pos;
	Coord lastPos;

	Model* model;

	EntityData data;
	EntityType *type;

	EntityManager *manager = nullptr;

	bool dirty = false;
};

class EntityManager : public Renderer {
public:
	//Constructors
	EntityManager();
	EntityManager(Field*);

	virtual ~EntityManager();

	//Get information
	Entity* getEntityAt(Coord) const;
	std::vector<Entity*> getEntities() const;

	//Renderer
	void draw() const;
	void redraw() const;

	//Add/remove from list
	bool registerEntity(Entity*);
	bool unregisterEntity(Entity*);

	//Take action
	bool moveEntity(Entity*, Coord);

	//Query
	bool inBounds(Coord) const;
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
