#include "world.h"

Player::Player(){}

Player::Player(int& hp, int& dmg, Room* pos) : hp(hp), damage(dmg), position(pos)
{}


void Player::Stats()
{
	printf("HP: %i\n", hp);
	printf("Damage: %i", damage);
}




Player::~Player()
{}