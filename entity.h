#ifndef _ENTITY_
#define _ENTITY_

#include "dlist.h"
#include "string.h"

enum Shape{ ROOM = 0, EXIT, CREATURE, ITEM };

class Entity
{
public:
	String name;
	String description;
	Shape shape;

	Dlist <Entity*> list;
	
	Entity();
	Entity(const char* name, const char* description, const Shape shape);
	virtual void Look(){};
	~Entity();
};


#endif