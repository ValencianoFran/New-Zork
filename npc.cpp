#include "npc.h"

NPC::NPC(const char* name, const char* description, Room* place, const int& hp, const int& money, Shape shape)
: Entity(name, description, shape), place(place), hp(hp), money(money)
{}

NPC::~NPC()
{}