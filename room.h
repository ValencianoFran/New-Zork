#ifndef _ROOMS__
#define _ROOMS__

#include"Entity.h"

class Room : public Entity
{
public:
	bool item_required; // Requires an item to access
	Room(const char* name, const char* description, const Shape shape, const bool item_required);
	~Room();
};

#endif