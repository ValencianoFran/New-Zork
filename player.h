#ifndef _PLAYER__
#define _PLAYER__

#include "world.h"
#include "Entity.h"
#include "items.h"

class Player :public Entity
{
public:
	bool head = false;
	bool hand = false;
	bool drive = false;

	int hp = 10;
	int damage = 10;

	unsigned int num_items = 0;
	unsigned int bag_capacity = 5;

	Room* position;

	Player();
	Player(int&, int&, Room*);
	void Stats();
	void Go(const String&);
	void Look(const String&);
	int Item_verification(const String&);
	int Direction(const String&);
	void Close(const String&);
	void Open(const String&);
	void Pick(const String&);
	void Drop(const String&);
	void Equip(const String&);
	void Unequip(const String&);
	void Put(const String&, const String&);
	void Get(const String&, const String&);
	void Attack(const String&);
	int Creature_verification(const String&);
	void Buy(const String&, const String&);
	~Player();
};

#endif