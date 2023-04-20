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
#include <set>

#include "area.hpp"
#include "field.hpp"
#include "pos.hpp"

#include "model.hpp"
#include "update.hpp"

#include "render.hpp"
#include "component.hpp"

/*	Types		*/
class EntityManager;
class Entity;

struct EntityData {
	int id;
	int state;
	std::string name;
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

/*
 * Reduce Entity to basic info (pos, name, etc.)
 * Allow collision, physics, model, etc. to be attached
 */
class Entity : public Update {
public:
	friend class EntityManager;

	//Constants
	const static Coord origin;
	const static std::string dName;

	//Constructors
	Entity(Coord=Coord(), EntityType* =nullptr, std::string=Entity::dName);

	//Action
	int sendAction(Entity*, EntityAction);
	int receiveAction(EntityAction);

	//Interaction
	virtual bool move(Coord);
	virtual bool moveInto(Entity*);

	//IModelable interface
	Coord getPos() const;
	Coord getLastPos();
	bool isDirty();

	//Components
	void attachComponent(ComponentBase*);
	void detachComponent(ComponentBase*);

	template<typename T> T* getComponent();
	template<typename T> std::set<T*> getComponents();

	template<typename T, class... Args> T* createComponent(Args...);
	template<typename T> void destroyComponent(T*);


	friend std::ostream& operator<<(std::ostream& out, const Entity& entity) {
		out << entity.data.name;
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

	EntityData data;
	EntityType *type;

	std::unordered_map<int, std::unordered_set<ComponentBase*>> components;

	EntityManager *manager = nullptr;

	bool dirty = false;
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




/********** TEMPLATE METHODS **********/

template<typename T>
T* Entity::getComponent() {
	int componentID = Component<T>::getComponentID();

	if(this->components.count(componentID) == 0)
		return nullptr;

	std::set<ComponentBase*> components = this->components[componentID];

	if(components.size() == 0)
		return nullptr;

	return dynamic_cast<T*>(*components.begin());
};

template<typename T>
std::set<T*> Entity::getComponents() {
	int componentID = Component<T>::getComponentID();

	if(this->components.count(componentID))
		return reinterpret_cast<std::set<T*>>(this->components[componentID]);
	else
		return std::set<T*>();
};


/*
 * Creates and attaches a component
 */
template<typename T, class... Args>
T* Entity::createComponent(Args... args) {
	int componentID = Component<T>::getComponentID();

	if(this->components.count(componentID) == 0)
		this->components.emplace();

	T* v = new T(args...);

	this->components[componentID].insert(v);

	return v;
};

/*
 * Destroys an attached component
 */
template<typename T>
void Entity::destroyComponent(T *component) {
	int componentID = Component<T>::getComponentID();

	if(this->components.count(componentID) == 0) return;

	typename decltype(this->components)::iterator iter = this->components[componentID].find(component);

	//Ensure that the component is attached to this entity
	if(iter == this->components.end()) return;

	delete *iter;

	this->components.erase(component);
};

#endif
