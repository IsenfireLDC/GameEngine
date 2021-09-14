/*
 * model.hpp
 *
 * Contains color and model types
 */

#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include <iostream>
#include <vector>


typedef char Color;
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

#endif
