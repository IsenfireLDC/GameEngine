#ifndef _UPDATE_HPP_
#define _UPDATE_HPP_

#include <unordered_set>
#include <unordered_map>

#include "threads.hpp"

template<typename T> class UpdateBase;

class UpdateControllerBase {
protected:
	static class Level *const defaultLevel;
	static class ThreadPool *const defaultThreadPool;
};

/*
 * Controller class used to perform updates on the template update class
 *
 * All instances for a given template type will act on the same objects, but
 * each instance will use its own thread pool
 */
template<typename T>
class UpdateController : public UpdateControllerBase {
public:
	friend UpdateBase<T>;

	UpdateController(class Level* = UpdateControllerBase::defaultLevel, ThreadPool* = UpdateControllerBase::defaultThreadPool);
	~UpdateController();

	/*
	 * Call the update method of T type update class
	 */
	void update(float);

private:
	class Level *level;
	ThreadPool *threadPool;

	static std::unordered_map<class Level*, std::unordered_set<T*>> members;
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

	UpdateBase(class Level*);
	virtual ~UpdateBase();

	virtual void update(float) = 0;

protected:
	bool doUpdate;
	class Level *level;
};


/*
 * Update class for frame-based updates
 */
class Update : public UpdateBase<Update> {
public:
	Update(class Level*);
	virtual ~Update();

	virtual void update(float) = 0;
};


/********** TEMPLATE METHODS **********/

template<typename T> std::unordered_map<class Level*, std::unordered_set<T*>> UpdateController<T>::members{};

/*
 * Create a controller instance attached to the given thread pool
 * Uses Engine::threadPool by default
 */
template<typename T>
UpdateController<T>::UpdateController(class Level *level, ThreadPool *threadPool) : level(level), threadPool(threadPool) {};

template<typename T>
UpdateController<T>::~UpdateController() {};

/*
 * Update all registered objects with the controller's thread pool
 */
template<typename T>
void UpdateController<T>::update(float delta) {
	for(T *update : UpdateController<T>::members[this->level]) {
		if(update->doUpdate)
			this->threadPool->add(std::bind(&T::update, update, delta));
	};
};


/*
 * Registers this object to the update controller for this type
 */
template<typename T>
UpdateBase<T>::UpdateBase(class Level *level) {
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
