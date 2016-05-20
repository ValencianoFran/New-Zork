#include "world.h"

Player::Player(){}

Player::Player(int& hp, int& dmg, Room* pos) : hp(hp), damage(dmg), position(pos)
{}

Player::~Player()
{}