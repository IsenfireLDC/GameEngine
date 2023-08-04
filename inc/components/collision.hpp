#ifndef _COMPONENTS_COLLISION_HPP_
#define _COMPONENTS_COLLISION_HPP_

#include "component.hpp"
#include "update.hpp"

#include <unordered_set>

class CollisionComponent : public Update {
public:
	CollisionComponent();
	virtual ~CollisionComponent();

	bool isCollidingWith(class Entity*);

	const std::unordered_set<class Entity*>& getCollisions(void);


	// Update
	virtual void update(float) = 0;

protected:
	std::unordered_set<class Entity*> collisions;
};


class RectCollisionComponent : public Component<RectCollisionComponent>, public CollisionComponent {
public:
	RectCollisionComponent(class RectArea*);
	virtual ~RectCollisionComponent();

	// Update
	void update(float);

private:
	class RectArea *area;
};

#endif
