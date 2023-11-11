/*
 * entity.hpp
 *
 * Used for managing entities
 */

#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <vector>
#include <iostream>

#include <unordered_map>
#include <set>

#include "vector.hpp"

#include "update.hpp"

#include "component.hpp"

/*	Types		*/
/*
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
//std::unordered_map<int, EntityActionHandler> handlers; //Map example for handlers
*/


/*
 * Reduce Entity to basic info (pos, name, etc.)
 * Allow collision, physics, model, etc. to be attached
 */
class Entity : public Update {
public:
	//Constants
	const static Vector2D origin;
	const static std::string defaultName;
	static class Level *const defaultLevel;

	//Constructors
	Entity(std::string=Entity::defaultName, class Level* = Entity::defaultLevel, Vector2D=Entity::origin);
	Entity(std::string, Vector2D, class Level* = Entity::defaultLevel);
	virtual ~Entity();

	// No copy constructor/assignment operator
	Entity(const Entity&) = delete;
	Entity operator=(const Entity&) = delete;

	//Update
	void update(float);

	//Action
	//int sendAction(Entity*, EntityAction);
	//int receiveAction(EntityAction);

	//Components
	void attachComponent(ComponentBase*);
	void detachComponent(ComponentBase*);

	template<typename T> T* getComponent();
	template<typename T> std::unordered_set<T*> getComponents();

	template<typename T, class... Args> T* createComponent(Args...);
	template<typename T> void destroyComponent(T*);


	friend std::ostream& operator<<(std::ostream& out, const Entity& entity) {
		out << entity.name;
		out << " id=" << (int)entity.id;
		//out << " type=" << (int)entity.type->id;
		out << " at" << entity.pos;
		return out;
	};


	Vector2D pos;
	std::string name;

	class Level *level;

private:
	static int gID;

	int id;
	int state;

	std::unordered_map<int, std::unordered_set<ComponentBase*>> components;

	bool dirty = false;
};




/********** TEMPLATE METHODS **********/

template<typename T>
T* Entity::getComponent() {
	int componentID = Component<T>::getComponentID();

	if(this->components.count(componentID) == 0)
		return nullptr;

	std::unordered_set<ComponentBase*> &components = this->components[componentID];

	if(components.size() == 0)
		return nullptr;

	return dynamic_cast<T*>(*components.begin());
};

template<typename T>
std::unordered_set<T*> Entity::getComponents() {
	int componentID = Component<T>::getComponentID();

	if(this->components.count(componentID)) {
		std::unordered_set<T*> typeSet;

		for(ComponentBase *base : this->components[componentID]) typeSet.insert((T*)base);

		return typeSet;
	} else
		return std::unordered_set<T*>();
};


/*
 * Creates and attaches a component
 */
template<typename T, class... Args>
T* Entity::createComponent(Args... args) {
	int componentID = Component<T>::getComponentID();

	if(this->components.count(componentID) == 0)
		this->components.emplace(componentID, std::unordered_set<ComponentBase*>());

	T* v = new T(this, args...);

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
