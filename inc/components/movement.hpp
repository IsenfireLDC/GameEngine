#ifndef _COMPONENT_MOVEMENT_HPP_
#define _COMPONENT_MOVEMENT_HPP_

#include "component.hpp"
#include "update.hpp"

class MovementComponent : public Component<MovementComponent>, public Update {
public:
	MovementComponent();
	virtual ~MovementComponent();

	//Update
	void update(float);

private:
};

#endif
