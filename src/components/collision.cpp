#include "components/collision.hpp"

#include "area.hpp"
#include "entity.hpp"
#include "level.hpp"

#include "engine.hpp"

CollisionComponentBase::CollisionComponentBase() : FixedUpdate(&Engine::level) {};

CollisionComponentBase::~CollisionComponentBase() {};


bool CollisionComponentBase::isCollidingWith(Entity *entity) const {
	return this->collisions.count(entity) > 0;
};

const std::unordered_set<Entity*>& CollisionComponentBase::getCollisions(void) const {
	return this->collisions;
};


RectCollisionComponent::RectCollisionComponent(Entity *entity, Coord size) : CollisionComponent(entity),
	collider(&entity->pos, size) {};

RectCollisionComponent::~RectCollisionComponent() {};


void RectCollisionComponent::update(float delta) {
	this->collisions.clear();

	this->addCollisions<RectCollisionComponent>(&this->collider);
};
