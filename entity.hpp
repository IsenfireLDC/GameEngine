/*
 * entity.hpp
 *
 * Used for managing entities
 */

#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#ifdef ERROR
#define _ENTITY_HPP_ERROR ERROR
#undef ERROR
#endif

/*	Types		*/
class Entity;


typedef struct {
	int x;
	int y;
} Coord;

enum class EntityType {
	ERROR,
	NONE,
	CONTROLLABLE,
	NPC,
	BARRIER
};

class Entity {
public:
	//Constructors
	Entity();
	Entity(EntityType, Coord, Coord);

	//Setters
	void setType(EntityType);
	void move(Coord);
	void moveBack();

	//Getters
	EntityType getType() const;
	Coord getPosition() const;
	Coord getLastPosition() const;

	//Actions
	void onMove();
	void onHit(Entity*);

	//Responses
	void onHitBy(Entity*);

private:
	EntityType type;
	Coord curr;
	Coord prev;
};

class EntityManager {
public:
	//Constructors
	EntityManager();
	EntityManager(int, int);

	//Destructor
	~EntityManager();

	//Constants
	const int defaultXSize = 51;
	const int defaultYSize = 21;

	//Getter
	Entity* getEntityAt(Coord) const;

	//Setter
	bool addEntity(Entity*);

	//Action
	bool moveEntity(Entity*, Coord);

private:
	void reallocateEntityList(int);

	//List of all entities
	Entity** entities;
};


#ifdef _ENTITY_HPP_ERROR
#define ERROR _ENTITY_HPP_ERROR
#undef _ENTITY_HPP_ERROR
#endif

#endif
