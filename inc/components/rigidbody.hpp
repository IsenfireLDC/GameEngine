#ifndef _COMPONENTS_RIGIDBODY_HPP_
#define _COMPONENTS_RIGIDBODY_HPP_

#include "component.hpp"
#include "update.hpp"
#include "vector.hpp"

class Entity;
class CollisionComponentBase;

/*
 * TODO: Separate into physics and component classes?
 * physics/rigidbody
 * components/rigidbody
 *
 * And same for collision, etc.?
 */
class RigidbodyComponent : public Component<RigidbodyComponent>, public FixedUpdate {
public:
	RigidbodyComponent(Entity*, CollisionComponentBase*);
	~RigidbodyComponent();

	void move(const Vector2D&);
	void push(const Vector2D&);

	// [FixedUpdate]
	void update(float);

	CollisionComponentBase *collisionComponent; //TODO: private?
	float mass;

	Vector2D velocity;

private:
	Vector2D position;

	Vector2D nextPosition;
};

#endif
