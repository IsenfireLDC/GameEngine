#include "components/collision.hpp"

#include "area.hpp"
#include "entity.hpp"
#include "level.hpp"

#include "engine.hpp"

inline void CollisionComponentBase::ensureValidCache(void) {
	if(!this->cacheValid) {
		this->cacheLock.lock();
		if(!this->cacheValid) {
			this->updateCache();
			this->cacheValid = true;
		};
		this->cacheLock.unlock();
	};
};


CollisionComponentBase::CollisionComponentBase() : FixedUpdate(&Engine::level) {
	this->cacheValid = false;
};

CollisionComponentBase::~CollisionComponentBase() {};


bool CollisionComponentBase::isCollidingWith(Entity *entity) {
	ensureValidCache();

	return this->collisions.count(entity) > 0;
};

const std::unordered_set<Entity*>& CollisionComponentBase::getCollisions(void) {
	ensureValidCache();

	return this->collisions;
};

void CollisionComponentBase::update(float delta) {
	(void)delta; //Unused

	// Require a cache update for this physics tick
	this->cacheValid = false;
};


RectCollisionComponent::RectCollisionComponent(Entity *entity, Vector2D size) : CollisionComponent(entity),
	collider(&entity->position, size) {};

RectCollisionComponent::~RectCollisionComponent() {};


void RectCollisionComponent::updateCache(void) {
	this->collisions.clear();

	this->addCollisions<RectCollisionComponent>(&this->collider);
};
