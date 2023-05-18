#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include <unordered_set>
#include <string>

class Level {
public:
	Level();
	virtual ~Level();

	void addEntity(class Entity*);
	void removeEntity(class Entity*);

	bool hasEntity(class Entity*) const;
	class Entity* findEntity(std::string) const;

private:
	std::unordered_set<class Entity*> entities;
};

/*
 * TODO: In component?
 * Add location-based entity search
 * Add component-based entity search
 */

#endif
