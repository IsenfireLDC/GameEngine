#ifndef _COMPONENTS_MODEL_HPP_
#define _COMPONENTS_MODEL_HPP_

#include "component.hpp"

class ModelComponent : public Component<ModelComponent> {
public:
	ModelComponent(class Entity*, class Model*);

	void setModel(class Model*);
	class Model* getModel() const;

private:
	class Model *model;
};

#endif
