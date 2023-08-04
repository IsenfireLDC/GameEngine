#include "components/collision.hpp"

#include "area.hpp"
#include "entity.hpp"
#include "level.hpp"

#include "engine.hpp"

CollisionComponent::CollisionComponent() : FixedUpdate(&Engine::level) {};

CollisionComponent::~CollisionComponent() {};


bool CollisionComponent::isCollidingWith(Entity *entity) {
	return this->collisions.count(entity) > 0;
};

const std::unordered_set<Entity*>& CollisionComponent::getCollisions(void) {
	return this->collisions;
};



RectCollisionComponent::RectCollisionComponent(Entity *entity, Coord size) : Component(entity), area(&this->entity->pos, size) {};

RectCollisionComponent::~RectCollisionComponent() {};


void RectCollisionComponent::update(float delta) {
	this->collisions.clear();

	for(RectCollisionComponent *other : Component<RectCollisionComponent>::instances) {
		if(!other) continue;

		if(this->area.overlaps(&other->area)) this->collisions.insert(other->entity);
	};
};
