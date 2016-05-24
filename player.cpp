#include "world.h"

#define NUM_EXITS 16
#define INVALID -1

Player::Player(){}

Player::Player(int& hp, int& dmg, Room* pos) : hp(hp), damage(dmg), position(pos)
{}


void Player::Stats()
{
	printf("HP: %i\n", hp);
	printf("Damage: %i", damage);
}

void Player::Go(const String& op) //Move player
{
	int  i = 0;
	bool finish = false;   //Check if go action is completed
	int direction = Direction(op); //Translate String into enum

		for (i = 0; i < NUM_EXITS; i++)
		{
			if ((world->entity[i]->shape == EXIT && ((Exit*)world->entity[i])->origin == this->position))
			{
				if (((Exit*)world->entity[i])->direction == direction)
				{
					if (exit[i]->destination == room[1] && item[4]->equipped == false)///////////////////////////////
					{
						printf("You need have googles equiped to do snorquel\n");
						finish = true;
						break;
					}
					if (exit[i]->destination == room[2] && item[9]->equipped == false)
					{
						printf("You need have boat equiped\n");
						finish = true;
						break;
					}
					if (exit[i]->close == true)
					{
						printf("The door is closed\n");
						finish = true;
						break;
					}
					else{
						player->position = exit[i]->destination;
						printf("\nYou are in %s\n\n%s \n", player->position->name.c_str(), player->position->description.c_str());

						finish = true;
						break;
					}
				}
			}
		}
		if (finish == false)
		{
			printf("\nThere is nothing there, you can't go this way\n");
		}
}


int Player::Direction(const String& op) //Check the direction is valid
{

	if (op == "north" || op == "n")
	{
		return 0;
	}
	if (op == "south" || op == "s")
	{
		return 1;
	}
	if (op == "east" || op == "e")
	{
		return 2;
	}
	if (op == "west" || op == "w")
	{
		return 3;
	}
	if (op == "up" || op == "u")
	{
		return 4;
	}
	if (op == "down" || op == "d")
	{
		return 5;
	}
	return INVALID;
}





Player::~Player()
{}