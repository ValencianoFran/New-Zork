#ifndef _ITEMS__
#define _ITEMS__

#include "Entity.h"
#include "string.h"
#include "vector.h"
#include "room.h"
#include "player.h"


enum equip
{
	Head,
	Hand,
	Cant_Equip,
	Drive
};

class Items : public Entity
{
public:

	Vector<Items*> chest; // List of items that this item can contain
	Room* place;
	bool container = false; //This item can contain more items
	bool inside = false; //This item can be inside another
	bool already_inside = false;
	bool picked = false; //This item is in the enventary
	bool equipped = false; //  This item is equiped
	equip slot; // What slot uses
	int item_hp;
	int item_damage;

	Items();
	~Items();
	Items(const char* name, const char* description, Room*, const int& hp, const int& dmg, const equip, const bool& container, const bool& inside, const bool& already_inside, Shape shape);
	void Look()const;
};


#endif