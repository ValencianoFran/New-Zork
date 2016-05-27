#include "creatures.h"

Creatures::Creatures(const char* name, const char* description, Room* place, const int& hp, const int& dmg, Shape shape)
: Entity(name, description, shape), place(place), hp(hp), damage(dmg)
{}

Creatures::~Creatures()
{}