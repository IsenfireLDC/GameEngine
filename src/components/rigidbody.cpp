#include "components/rigidbody.hpp"

#include "entity.hpp"
#include "collider.hpp"

RigidbodyComponent::RigidbodyComponent(Entity *parent, Collider *collider) : Component(parent), collider(collider) {};
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
	this->parent->position = this->nextPosition + this->velocity * delta;

	// TODO: Using `Collider`, not `CollisionComponent`.  Oops
	// Which one should be used?
	//
	// Check for collisions
	const std::unordered_set<Entity*>& collisions = this->collider->getCollisions();

	// Reset position on collision
	if(!collisions.empty()) this->parent->position = this->position;
	else this->position = this->nextPosition;
};
