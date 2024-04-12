#ifndef _COMPONENTS_COLLISION_HPP_
#define _COMPONENTS_COLLISION_HPP_

#include "component.hpp"
#include "update.hpp"
#include "vector.hpp"
#include "collider.hpp"

#include "entity.hpp"

#include <unordered_set>
#include <mutex>

class CollisionComponentBase : public FixedUpdate {
public:
	CollisionComponentBase();
	virtual ~CollisionComponentBase();

	// Single/multi collision check
	bool isCollidingWith(class Entity*);
	const std::unordered_set<class Entity*>& getCollisions(void);

	// Fixed Update
	void update(float);

protected:
	// To be implemented by specific base class, actually calculates the collisions
	virtual void updateCache(void) = 0;

	std::unordered_set<class Entity*> collisions;

private:
	// Helper to refresh cache, if necessary
	inline void ensureValidCache(void);

	bool cacheValid;
	std::mutex cacheLock;
};

template<typename T>
class CollisionComponent : public CollisionComponentBase, public Component<T> {
public:
	CollisionComponent(class Entity *entity) : Component<T>(entity) {};
	virtual ~CollisionComponent() {};

protected:
	// Helper for specific base class to calculate collisions using Collider
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
		if(entity == this->entity) continue;

		for(C *other : entity->getComponents<C>()) {
			if(collider->isCollidingWith(&other->collider)) this->collisions.insert(entity);
		};
	};
};

#endif
