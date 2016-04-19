#ifndef _ENTITY_
#define _ENTITY_

#include "string.h"

class Entity
{
public:
	String name;
	String description;
	Entity();
	Entity(const char* _name, const char* _description);
	~Entity();
};


#endif