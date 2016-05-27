#ifndef _CREATURES_
#define _CREATURES_
#include "entity.h"
#include "room.h"

class Creatures : public Entity
{
public:
	
	int hp = 0;
	int damage = 0;
	Room* place = nullptr;

	Creatures(const char* name, const char* description, Room*, const int& hp, const int& dmg, Shape shape);
	~Creatures();
};


#endif