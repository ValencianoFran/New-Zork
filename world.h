#ifndef _WORLD__
#define _WORLD__

#include "room.h"
#include "player.h"
#include "exit.h"
#include "Entity.h"
#include "string.h"
#include "vector.h"
#include "items.h"

class Items;
class Player;

class World : public Entity
{
public:
	Vector <Room*> room;
	Vector <Exit*> exit;
	Vector <Items*> item;
	Player* player;

	World();
	~World();
	void Tutorial() const;
	void CreatePlayer() const;
	void CreateWorld();

	void Mayus(String&);
	void Go(const String&);
	int Direction(const String&);
	void Action(Vector <String>&, const int& space);
	int Item_verification(const String&);
	void Look(const String&);
	void Close(const String&);
	void Open(const String&);
	void Pick(const String&);
	void Drop(const String&);
	void Equip(const String&);
	void Unequip(const String&);
	void Put(const String&, const String&);
	void Get(const String&, const String&);
	void Inventory();

};

#endif