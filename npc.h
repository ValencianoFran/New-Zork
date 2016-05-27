#ifndef _NPC_
#define _NPC_
#include "entity.h"
#include "room.h"

class NPC : public Entity
{
public:

	int hp = 0;
	int money = 0;
	Room* place = nullptr;

	NPC(const char* name, const char* description, Room*, const int& hp, const int& money, Shape shape);
	~NPC();
};


#endif