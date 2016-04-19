#ifndef _PLAYER__
#define _PLAYER__

#include "world.h"
#include "Entity.h"
#include "items.h"

class Player :public Entity
{
public:
	Room* position;
	Player();
	~Player();
	Player(int&, int&, Room*);
	bool _head = false;
	bool _hand = false;
	bool _drive = false;
	int hp = 10;
	int damage = 10;
	unsigned int num_items = 0;
	unsigned int bag_capacity = 10;
};

#endif