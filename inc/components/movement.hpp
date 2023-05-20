#ifndef _COMPONENT_MOVEMENT_HPP_
#define _COMPONENT_MOVEMENT_HPP_

#include "component.hpp"

class MovementComponent : public Component<MovementComponent> {
public:
	MovementComponent();
	virtual ~MovementComponent();

private:
};

#endif
