#include "world.h"

Player::Player(){}

Player::Player(int& _hp, int& _dmg, Room* _pos)
{
	hp = _hp;
	damage = _dmg;
	position = _pos;
}

Player::~Player()
{}