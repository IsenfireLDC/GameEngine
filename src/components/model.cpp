#include "components/model.hpp"

#include "model.hpp"

/*
 * Create component with the given model
 */
ModelComponent::ModelComponent(Entity *entity, Model *model) : Component(entity) {
	this->model = model;
};


/*
 * Attach a new model to the component
 */
void ModelComponent::setModel(Model *model) {
	this->model = model;
};

/*
 * Return the model attached to this component
 */
Model* ModelComponent::getModel() const {
	return this->model;
};
