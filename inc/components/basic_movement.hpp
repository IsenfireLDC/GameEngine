#ifndef _COMPONENT_BASIC_MOVEMENT_HPP_
#define _COMPONENT_BASIC_MOVEMENT_HPP_

#include "component.hpp"
#include "update.hpp"

class BasicMovementComponent : public Component<BasicMovementComponent>, public Update {
public:
	BasicMovementComponent();
	virtual ~BasicMovementComponent();

	//Update
	void update(float);

private:
};

#endif