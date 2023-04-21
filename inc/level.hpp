#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include <unordered_set>

class Level {
public:
	Level();
	virtual ~Level();

	void addEntity(class Entity*);
	void removeEntity(class Entity*);

private:
	std::unordered_set<class Entity*> entities;
};

#endif
