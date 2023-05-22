#ifndef _UPDATE_HPP_
#define _UPDATE_HPP_

#include <unordered_set>
#include <unordered_map>

#include "threads.hpp"
#include "level.hpp"

#include "engine.hpp"

template<typename T> class UpdateBase;

/*
 * Controller class used to perform updates on the template update class
 *
 * All instances for a given template type will act on the same objects, but
 * each instance will use its own thread pool
 */
template<typename T>
class UpdateController {
public:
	friend UpdateBase<T>;

	UpdateController(Level* = &Engine::level, ThreadPool* = &Engine::threadPool);
	~UpdateController();

	/*
	 * Call the update method of T type update class
	 */
	void update(float);

private:
	Level *level;
	ThreadPool *threadPool;

	static std::unordered_map<Level*, std::unordered_set<T*>> members;
};

/*
 * Base class for adding update support
 *
 * Uses CRTP to handle per-type object registration automatically
 */
template<typename T>
class UpdateBase {
public:
	friend UpdateController<T>;

	UpdateBase(Level*);
	virtual ~UpdateBase();

	virtual void update(float) = 0;

protected:
	bool doUpdate;
	Level *level;
};


/*
 * Update class for frame-based updates
 */
class Update : public UpdateBase<Update> {
public:
	Update(Level*);
	virtual ~Update();

	virtual void update(float) = 0;
};


/********** TEMPLATE METHODS **********/

template<typename T> std::unordered_map<Level*, std::unordered_set<T*>> UpdateController<T>::members{};

/*
 * Create a controller instance attached to the given thread pool
 * Uses Engine::threadPool by default
 */
template<typename T>
UpdateController<T>::UpdateController(Level *level, ThreadPool *threadPool) : level(level), threadPool(threadPool) {};

template<typename T>
UpdateController<T>::~UpdateController() {};

/*
 * Update all registered objects with the controller's thread pool
 */
template<typename T>
void UpdateController<T>::update(float delta) {
	for(UpdateBase<T> *update : UpdateController<T>::members[this->level]) {
		if(update->doUpdate)
			this->threadPool->add(std::bind(update->update, update, delta));
	};
};


/*
 * Registers this object to the update controller for this type
 */
template<typename T>
UpdateBase<T>::UpdateBase(Level *level) {
	UpdateController<T>::members[level].insert(static_cast<T*>(this));

	this->doUpdate = true;
	this->level = level;
};

/*
 * Unregisters this object from the update controller for this type
 */
template<typename T>
UpdateBase<T>::~UpdateBase() {
	UpdateController<T>::members[this->level].erase(static_cast<T*>(this));
};

#endif
