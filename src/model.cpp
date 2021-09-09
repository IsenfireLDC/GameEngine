/*
 * model.cpp
 *
 * Create color and model types
 * Manage models
 */

#include "model.hpp"

#include <iterator>
#include <algorithm>

/*
 * Constructor for default model manager
 */
ModelManager::ModelManager() {
	this->models = std::vector<Model*>();
};

/*
 * Creates a new model and returns the id
 */
int ModelManager::createModel(char mChar, Color color) {
	int index = this->models.size();
	this->models.push_back(new Model(mChar, color));

	return index;
};

/*
 * Adds existing model and returns the id
 */
int ModelManager::addModel(Model* model) {
	int index = this->models.size();
	this->models.push_back(model);

	return index;
};

/*
 * Replace existing model added with addModel
 */
void ModelManager::replaceModel(int id, Model *model) {
	std::vector<Model*>::iterator pos = this->models.begin()+id;
	this->models.erase(pos);
	this->models.insert(pos+1, model);
};

/*
 * Delete model created with createModel
 */
void ModelManager::deleteModel(int id) {
	delete this->models.at(id);
	this->models.erase(this->models.begin()+id);
};

/*
 * Remove model added with addModel
 */
void ModelManager::removeModel(Model *model) {
	std::vector<Model*>::iterator pos = std::find(
		this->models.begin(),
		this->models.end(),
		model
	);

	if(pos != this->models.end())
		this->models.erase(pos);
};

/*
 * Get model with the given id
 */
Model* ModelManager::getModel(int id) const {
	return this->models.at(id);
};
