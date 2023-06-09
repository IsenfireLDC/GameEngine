#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include "render.hpp"
#include "model.hpp"

#include <unordered_set>

/*
 * Represents a drawable window
 *
 * Handles drawing output and passing back input
 */
class Window : public Renderer {
public:
	static BasicModel defaultBorder;
	static BasicModel defaultBackground;

	//Constructors
	Window(RectArea = RectArea(), Coord = Coord(1,1),
		BasicModel* = &defaultBorder,
		BasicModel* = &defaultBackground
	);

	//Getters
	Coord size() const;
	Coord getScale() const;

	BasicModel* getBorderModel() const;
	BasicModel* getBackgroundModel() const;

	//Setters
	void setMsg(const char*);

	void resize(Coord);
	void setScale(Coord);

	void setBorderModel(BasicModel*);
	void setBackgroundModel(BasicModel*);

	void addRenderer(Renderer*);
	void removeRenderer(Renderer*);

	void addRenderers(std::vector<Renderer*>&);

	//Rendering
	void draw() const;
	void redraw() const;
	void clear() const;


	std::function<void(BoundingBox)> getBackground() const;

	void show(bool);

private:
	void drawBackground(BoundingBox) const;

	RectArea area;
	Coord scale;

	BoundingBox windowBB;

	BasicModel *border;
	BasicModel *background;

	bool visible;

	std::unordered_set<const Renderer*> models;

	const char * msg = nullptr;
};

#endif
