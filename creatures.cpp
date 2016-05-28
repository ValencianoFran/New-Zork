#include "creatures.h"

Creatures::Creatures(const char* name, const char* description, Room* place, const int& hp, const int& dmg, const int& money, const bool& state, Shape shape)
: Entity(name, description, shape), place(place), hp(hp), damage(dmg), money(money), state_agressive(state)
{}



Creatures::~Creatures()
{}