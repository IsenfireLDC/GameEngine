#include "components/rigidbody.hpp"

#include "entity.hpp"
#include "components/collision.hpp"

#include "level.hpp"
#include "engine.hpp"

RigidbodyComponent::RigidbodyComponent(Entity *parent, CollisionComponentBase *collisionComponent) : Component(parent), FixedUpdate(&Engine::level), collisionComponent(collisionComponent) {};
RigidbodyComponent::~RigidbodyComponent() {};

// TODO: Add 'continuous' collision checks

void RigidbodyComponent::move(const Vector2D &position) {
	this->nextPosition = position;
};

void RigidbodyComponent::push(const Vector2D &force) {
	this->velocity += force / this->mass;
};


void RigidbodyComponent::update(float delta) {
	// Attempt to move
	this->entity->position = this->nextPosition + this->velocity * delta;

	// Check for collisions
	const std::unordered_set<Entity*>& collisions = this->collisionComponent->getCollisions();

	// Reset position on collision
	if(!collisions.empty()) this->entity->position = this->position;
	else this->position = this->nextPosition;
};
