#include "collider.hpp"

#include <unordered_set>

ColliderList Collider::colliders{};

Collider::Collider() {
	Collider::colliders.insert(this);
};

Collider::~Collider() {
	Collider::colliders.erase(this);
};


void ColliderList::insert(const Collider *collider) {
	this->colliders.insert(collider);
};

void ColliderList::erase(const Collider *collider) {
	this->colliders.erase(collider);
};

const std::unordered_set<const Collider*>& ColliderList::getColliders(const Collider *collider) const {
	return this->colliders;
};



RectCollider::RectCollider(const Vector2D *position, Vector2D size) : position(position), size(size) {};

RectCollider::~RectCollider() {};

bool RectCollider::isCollidingWith(const RectCollider *other) const {
	return
		this->position->x + this->size.x >= other->position->x &&
		this->position->x <= other->position->x + other->size.x &&
		this->position->y + this->size.y >= other->position->y &&
		this->position->y <= other->position->y + other->size.y;
};

bool RectCollider::isCollidingWith(const CircleCollider*) const { return false; };
bool RectCollider::isCollidingWith(const PolyCollider*) const { return false; };
