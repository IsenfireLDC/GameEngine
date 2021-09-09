/*
 * model.hpp
 *
 * Contains color and model types
 */

#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include <iostream>
#include <vector>


enum class ModelType {
	None,
	Dynamic,
	Static
};

typedef int Color;
struct Model {
	char model;
	Color color;

	Model(char model, Color color) {
		this->model = model;
		this->color = color;
	};

	friend std::ostream& operator<<(std::ostream &out, const Model &model) {
		out << model.model;
		return out;
	};
};

/**
 * A class to manage a list of models
 *
 * Provides method to add and remove models
 *
 * Stores models in a vector
 */
class ModelManager {
public:
	//Constructor
	ModelManager();

	//Add model to list
	int createModel(char, Color);	//new
	int addModel(Model*);		//existing

	//Replace existing model
	void replaceModel(int, Model*);

	//Remove model from list
	void deleteModel(int);		//new
	void removeModel(Model*);	//existing

	//Get model
	Model* getModel(int) const;

private:
	std::vector<Model*> models;
};

#endif
