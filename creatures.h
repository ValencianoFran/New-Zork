#ifndef _CREATURES_
#define _CREATURES_
#include "entity.h"
#include "room.h"

class Creatures : public Entity
{
public:
	
	int hp = 0;
	int damage = 0;
	int money = 0;
	bool state_agressive = false;
	Room* place = nullptr;

	Creatures(const char* name, const char* description, Room*, int hp, int dmg, int money, const bool state, Shape shape);
	

	
	~Creatures();
};


#endif