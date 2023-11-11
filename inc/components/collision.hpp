#ifndef _COMPONENTS_COLLISION_HPP_
#define _COMPONENTS_COLLISION_HPP_

#include "component.hpp"
#include "update.hpp"
#include "vector.hpp"
#include "collider.hpp"

#include "entity.hpp"

#include <unordered_set>

class CollisionComponentBase : public FixedUpdate {
public:
	CollisionComponentBase();
	virtual ~CollisionComponentBase();

	bool isCollidingWith(class Entity*);

	const std::unordered_set<class Entity*>& getCollisions(void);

	// Fixed Update
	void update(float);

protected:
	virtual void updateCache(void) = 0;

	std::unordered_set<class Entity*> collisions;

private:
	bool cacheValid; // TODO: Race conditions?
};

template<typename T>
class CollisionComponent : public CollisionComponentBase, public Component<T> {
public:
	CollisionComponent(class Entity *entity) : Component<T>(entity) {};
	virtual ~CollisionComponent() {};

protected:
	template<typename C>
	void addCollisions(const Collider*);
};


class RectCollisionComponent : public CollisionComponent<RectCollisionComponent> {
public:
	friend class CollisionComponent;

	RectCollisionComponent(class Entity*, Vector2D);
	~RectCollisionComponent();

protected:
	// Collisions update
	void updateCache(void);

private:
	const RectCollider collider;
};




/*** TEMPLATE METHODS ***/
template<typename T>
template<typename C>
void CollisionComponent<T>::addCollisions(const Collider *collider) {
	// Not sure why 'template' is necessary here, but it is
	for(Entity *entity : this->entity->level->template findEntitiesWithComponent<C>()) {
		for(C *other : entity->getComponents<C>()) {
			if(collider->isCollidingWith(&other->collider)) this->collisions.insert(entity);
		};
	};
};

#endif
