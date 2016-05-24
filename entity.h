#ifndef _ENTITY_
#define _ENTITY_

#include "dlist.h"
#include "string.h"

enum Shape{ ROOM, EXIT, PLAYER, ITEM };

class Entity
{
public:
	String name;
	String description;
	Shape shape;

	Dlist <Entity*> list;
	
	Entity();
	Entity(const char* name, const char* description);
	virtual void Look()
	{};
	~Entity();
};


#endif