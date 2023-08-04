#ifndef _COMPONENT_BASIC_MOVEMENT_HPP_
#define _COMPONENT_BASIC_MOVEMENT_HPP_

#include "component.hpp"
#include "update.hpp"

class BasicMovementComponent : public Component<BasicMovementComponent>, public Update {
public:
	BasicMovementComponent(class Entity*, float = 100.f);
	virtual ~BasicMovementComponent();

	//Update
	void update(float);

	float speed;
};

#endif
