#ifndef _PLAYER__
#define _PLAYER__

#include "world.h"
#include "creatures.h"
#include "Entity.h"
#include "room.h"
#include "items.h"

class Player :public Creatures
{
public:
	bool head = false;
	bool hand = false;
	bool drive = false;

	unsigned int num_items = 0;
	unsigned int bag_capacity = 5;

	Player(const char* name, const char* description, Room* place, int, int, int money, const bool state, Shape shape);
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
	void Sell(const String&, const String&);
	~Player();
};

#endif