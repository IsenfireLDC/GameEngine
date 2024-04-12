#ifndef _COMPONENT__MOVEMENT_HPP_
#define _COMPONENT__MOVEMENT_HPP_

#include "component.hpp"
#include "update.hpp"

#include "components/rigidbody.hpp"

class MovementComponent : public Component<MovementComponent>, public Update {
public:
	MovementComponent(class Entity*, float speed=100.f, RigidbodyComponent* =nullptr);
	virtual ~MovementComponent();

	//Update
	void update(float);

	float speed;
	RigidbodyComponent *rigidbody;
};

#endif

