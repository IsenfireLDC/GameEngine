#ifndef _COMPONENT_HPP_
#define _COMPONENT_HPP_

#include <vector>
#include <unordered_set>

class ComponentBase;

namespace Engine {
	extern int GCID;
};

class ComponentBase {
public:
	ComponentBase(class Entity*);

	virtual int componentID() const = 0;

	class Entity *entity = nullptr;
};

/*
 * Must hold some form of unique component id
 */
template<typename T>
class Component : public ComponentBase {
public:
	Component(class Entity *entity) : ComponentBase(entity), id(_getComponentID<T>()) {
		Component<T>::instances.insert(static_cast<T*>(this));
	};

	virtual ~Component() {
		Component<T>::instances.erase(static_cast<T*>(this));
	};

	int componentID() const {
		return this->id;
	};

	static int getComponentID() {
		return _getComponentID<T>();
	};

	// TODO: Attach this to a level?
	static std::unordered_set<T*> instances;

private:
	//6365115
	template<typename D>
	static int _getComponentID() {
		static int id = ++Engine::GCID;
		return id;
	};

private:
	const int id;
};

template<typename T>
std::unordered_set<T*> Component<T>::instances{};

#endif
