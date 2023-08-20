#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include <unordered_set>
#include <string>

//Need access to Entity methods in template
#include "entity.hpp"

class Level {
public:
	Level();
	virtual ~Level();

	void addEntity(Entity*);
	void removeEntity(Entity*);

	bool hasEntity(Entity*) const;
	Entity* findEntity(std::string) const;

	template<typename T>
	std::unordered_set<Entity*> findEntitiesWithComponent() const;

private:
	std::unordered_set<Entity*> entities;

	//Used for component search to enable caching results
	int modification;
};






/********** TEMPLATE METHODS **********/

// TODO: Consider returning a const reference for efficiency; should be safe as this should only update once a tick
template<typename T>
std::unordered_set<Entity*> Level::findEntitiesWithComponent() const {
	static int validFor = -1;
	static std::unordered_set<Entity*> withT;

	//Keep cached copy of set for faster access
	if(validFor == this->modification) return withT;

	validFor = this->modification;
	withT.clear();

	for(Entity *entity : this->entities) {
		T* t = entity->getComponent<T>();

		if(t) withT.insert(entity);
	};

	return withT;
};

/*
 * TODO: In component?
 * Add location-based entity search
 */

#endif
