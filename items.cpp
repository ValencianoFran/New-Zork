#include "items.h"

Items::Items()
{}

Items::Items(const char* name, const char* description, Room* place, const int& hp, const int& dmg, const equip slot, const bool& container, const bool& inside, const bool& already_inside)
: place(place), Entity(name, description), item_hp(hp), item_damage(dmg), slot(slot), container(container), inside(inside), already_inside(already_inside)
{}


void Items::Look()const
{
	printf("%s\n%s\n", name.c_str(), description.c_str()); 
}

Items::~Items()
{}