#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include "render.hpp"
#include "model.hpp"

/*
 * Represents a drawable window
 *
 * Handles drawing output and passing back input
 */
class Window : public Renderer {
public:
	//Constructors
	Window(RectArea = RectArea(), Coord = Coord(1,1));
	Window(RectArea, Coord,
		BasicModel = BasicModel('#', TermColor::GRAY),
		BasicModel = BasicModel(' ', TermColor::BG_DARK_GRAY)
	);

	//Getters
	Coord size() const;
	Coord getScale() const;

	BasicModel getBorderModel() const;
	BasicModel getBackgroundModel() const;

	//Setters
	void setMsg(const char*);

	void resize(Coord);
	void setScale(Coord);

	void setBorderModel(BasicModel);
	void setBackgroundModel(BasicModel);

	void addModel(const Model*);
	void removeModel(const Model*);

	void addModels(std::vector<const Model*>&);

	//Rendering
	void draw() const;
	void redraw() const;

	void show(bool);

private:
	void drawBackground(BoundingBox) const;

	RectArea area;
	Coord scale;

	BoundingBox windowBB;

	BasicModel border;
	BasicModel background;

	bool visible;

	std::vector<const ModelRenderer*> models;

	const char * msg = nullptr;
};

#endif
