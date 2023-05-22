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
	virtual int componentID() const = 0;

	class Entity *entity = nullptr;
};

/*
 * Must hold some form of unique component id
 */
template<typename T>
class Component : public ComponentBase {
public:
	Component() : id(_getComponentID<T>()) {};

	int componentID() const {
		return this->id;
	};

	static int getComponentID() {
		return _getComponentID<T>();
	};

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

#endif
