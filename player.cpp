#include "world.h"

#define INVALID -1

Player::Player(){}

Player::Player(int& hp, int& dmg, Room* pos) : hp(hp), damage(dmg), position(pos)
{}


void Player::Stats()
{
	printf("HP: %i\n", hp);
	printf("Damage: %i\n", damage);
}

void Player::Go(const String& op) //Move player
{
	int  i = 0;
	bool finish = false;   //Check if go action is completed
	int direction = Direction(op); //Translate String into enum

		for (i = 0; i < world->entity.Size(); i++)
		{
			if ((world->entity[i]->shape == EXIT && ((Exit*)world->entity[i])->origin == this->position))
			{
				if (((Exit*)world->entity[i])->direction == direction)
				{
					if (((Exit*)world->entity[i])->destination->item_required == true)
					{
						printf("You need an special item to come here\n");
						finish = true;
						break;
					}
					if (((Exit*)world->entity[i])->close == true)
					{
						printf("The door is closed\n");
						finish = true;
						break;
					}
					else
					{
						this->position = ((Exit*)world->entity[i])->destination;
						printf("\nYou are in %s\n\n%s \n", this->position->name.c_str(), this->position->description.c_str());

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

void Player::Look(const String& op) //Look the exit
{
	int direc = INVALID;
	int item = INVALID;
	int  i = 0, j = 0, saw_items = 0;
	bool finish = false;   //Check if go action is completed
	item = Item_verification(op); //Look if the item name is valid

	if (op == "look" || op == "l")
	{
		printf("\nYou see %s\n%s ", position->name.c_str(), position->description.c_str());
		printf("You can see this items:\n");
		
		for (j = 0; j < world->entity.Size(); j++)
		{
			if (world->entity[j]->shape == ITEM && ((Items*)world->entity[j])->place == position && ((Items*)world->entity[j])->picked == false && ((Items*)world->entity[j])->equipped == false && ((Items*)world->entity[j])->already_inside == false)
			{
				printf("%s:\t%s\n", ((Items*)world->entity[j])->name.c_str(), ((Items*)world->entity[j])->description.c_str());
				saw_items++;
			}
		}
		if (saw_items == 0) printf("There are no items here\n");
		finish = true;
		return;
	}

	direc = Direction(op); //Look if the direction name is valid
	if (direc == INVALID && item == INVALID)
	{
		printf("Invalid command\n");
		return;
	}

	if (direc != INVALID)
	{
		for (i = 0; i < world->entity.Size(); i++)
		{
			if (world->entity[i]->shape == EXIT && ((Exit*)world->entity[i])->origin == position) //Compares the player position with the origin room of the exit
			{
				if (((Exit*)world->entity[i])->direction == direc)
				{
					printf("\nYou see %s\n%s ", ((Exit*)world->entity[i])->name.c_str(), ((Exit*)world->entity[i])->description.c_str());
					finish = true;
					break;
				}
			}
		}
		if (finish == false)
		{
			printf("\nThere are nothing here\n");
		}
	}

	if (item != INVALID)
	{
		for (int j = 0; j < world->entity.Size(); j++)
		{
			if (((Items*)world->entity[j])->name == op)
			{
				((Items*)world->entity[i])->Look();
				return;
			}
		}
	}
}

int Player::Item_verification(const String& item)
{
	for (int j = 0; j < world->entity.Size(); j++)
	{
		if (((Items*)world->entity[j])->name == item)
		{
			return 1;
		}
	}
	return INVALID;
}

void Player::Open(const String& op) //Open doors
{
	int direc = INVALID;
	int i = 0;
	bool done = false;  //Check if go action is completed
	direc = Direction(op);  //Check if direction is valid

	if (direc == INVALID){
		printf("Invalid direction\n");
		return;
	}
	else
	{
		for (i = 0; i < world->entity.Size(); i++)
		{

			if (((Exit*)world->entity[i])->origin == position) //Compares the player position with the origin room of the exit
			{
				if (((Exit*)world->entity[i])->direction == direc)
				{
					if (((Exit*)world->entity[i])->close == true)
					{		// If the door is closed, open it
						((Exit*)world->entity[i])->close = false;
						printf("\nThe door is open\n");
						done = true;
						break;
					}

					else
					{
						break;
					}
				}
			}
		}
		if (done == false)
		{
			printf("\nThere is nothing to open or It's already open\n");
		}
	}
}

void Player::Close(const String& op) //Similar function of Open, but it closes the door
{
	int direc = INVALID;
	int i = 0;
	bool finish = false;
	direc = Direction(op);

	if (direc == INVALID)
	{
		printf("Invalid direction\n");
		return;
	}
	else
	{
		for (i = 0; i < world->entity.Size(); i++)
		{
			if (((Exit*)world->entity[i])->origin == position)
			{
				if (((Exit*)world->entity[i])->direction == direc)
				{
					if (((Exit*)world->entity[i])->close == false)
					{
						((Exit*)world->entity[i])->close = true;
						printf("The door is closed\n");
						finish = true;
						break;
					}
					else{
						break;
					}
				}
			}
		}


		if (finish == false){
			printf("There is no doors to close or It's already closed\n");
		}
	}
}

/*
void Player::Inventory()
{
	int done = 0;
	printf("You have this items in the inventory:\n");
	for (int j = 0; j <= 9; j++)
	{
		if (item[j]->picked == true && item[j]->equipped == false)
		{
			printf("%s\n", item[j]->name.c_str());
			done = 1;
		}
	}
	if (done == 0)
	{
		printf("You don't have items yet\n");
	}
	return;
}
*/



void Player::Pick(const String& item)
{
	int item_comprovant = INVALID;
	if (num_items >= bag_capacity)
	{
		printf("The bag is full\n");
		return;
	}

	item_comprovant = Item_verification(item);
	if (item_comprovant == INVALID)
	{
		printf("Thats a invalid item\n");
		return;
	}


	for (int j = 0; j < world->entity.Size(); j++)
	{
		if (((Items*)world->entity[j])->name == item && ((Items*)world->entity[j])->place == position)
		{
			if (((Items*)world->entity[j])->picked == false && ((Items*)world->entity[j])->equipped == false && ((Items*)world->entity[j])->already_inside == false)
			{
				((Items*)world->entity[j])->picked = true;
				printf("You picked %s\n", ((Items*)world->entity[j])->name.c_str());
				return;
			}
			if (((Items*)world->entity[j])->picked == false && ((Items*)world->entity[j])->equipped == false && ((Items*)world->entity[j])->already_inside == true)
			{
				printf("You must get the item from the container\n");
			}
		}
	}

	printf("You have already picked that item or it isn't here\n");
	return;
}

void Player::Drop(const String& _item)
{
	int item_comprovant = INVALID;
	item_comprovant = Item_verification(_item);
	if (item_comprovant == INVALID)
	{
		printf("Thats a invalid item\n");
		return;
	}

	for (int j = 0; j < world->entity.Size(); j++)
	{
		if (((Items*)world->entity[j])->name == _item)
		{
			if (((Items*)world->entity[j])->picked == true && ((Items*)world->entity[j])->equipped == false)
			{
				((Items*)world->entity[j])->picked = false;
				((Items*)world->entity[j])->place =position;
				printf("You dropped %s\n", ((Items*)world->entity[j])->name.c_str());
				return;
			}
		}
	}

	printf("You dont have that item in your inventary or It's equipped\n");
	return;

}
/*
void Player::Equip(const String& _item)
{
	int item_comprovant = INVALID;
	item_comprovant = Item_verification(_item);
	if (item_comprovant == INVALID)
	{
		printf("Thats a invalid item\n");
		return;
	}


	for (int j = 0; j <= 9; j++)
	{
		if (item[j]->name == _item)
		{
			if (item[j]->equipped == false && item[j]->picked == true)
			{
				if (item[j]->slot == 0 && player->head == false)
				{
					item[j]->equipped = true;
					item[j]->picked = false;
					player->head = true;
					printf("You equiped %s\n", item[j]->name.c_str());
					return;
				}
				if (item[j]->slot == 1 && player->hand == false)
				{
					item[j]->equipped = true;
					item[j]->picked = false;
					player->hand = true;
					printf("You equiped %s\n", item[j]->name.c_str());
					return;
				}

				if (item[j]->slot == 3 && player->drive == false)
				{
					item[j]->equipped = true;
					item[j]->picked = false;
					player->drive = true;
					printf("You equiped %s\n", item[j]->name.c_str());
					return;
				}

			}

			else
			{
				if (item[j]->slot == 0 && player->head == true)
				{
					printf("Actually your head is equiped\n");
				}
				if (item[j]->slot == 1 && player->hand == true)
				{
					printf("Actually your hand is equiped\n");
				}
				if (item[j]->slot == 3 && player->drive == true)
				{
					printf("Actually you have transport\n");
				}
				else
				{
					printf("You can't equip that item or you don't have it in the inventory\n");
				}
				return;
			}
		}
	}
}

void Player::Unequip(const String& _item)
{
	int item_comprovant = INVALID;
	item_comprovant = Item_verification(_item);
	if (item_comprovant == INVALID)
	{
		printf("Thats a invalid item\n");
		return;
	}

	for (int j = 0; j <= 9; j++)
	{
		if (item[j]->name == _item)
		{
			if (item[j]->equipped == true)
			{
				if (item[j]->slot == 0 && player->head == true)
				{
					item[j]->equipped = false;
					item[j]->picked = true;
					player->head = false;
					printf("You unequipped %s\n", item[j]->name.c_str());
					return;
				}
				if (item[j]->slot == 1 && player->hand == true)
				{
					item[j]->equipped = false;
					item[j]->picked = true;
					player->hand = false;
					printf("You unequipped %s\n", item[j]->name.c_str());
					return;
				}

				if (item[j]->slot == 3 && player->drive == true)
				{
					item[j]->equipped = false;
					item[j]->picked = true;
					player->drive = false;
					printf("You unequipped %s\n", item[j]->name.c_str());
					return;
				}
			}
			else
			{
				printf("You don't have equiped that item\n");
				return;
			}
		}
	}
}

void Player::Put(const String& _put, const String& _into)
{
	int finish = 0;
	int item_comprovant1 = INVALID;
	int item_comprovant2 = INVALID;
	item_comprovant1 = Item_verification(_put);
	item_comprovant2 = Item_verification(_into);
	if (item_comprovant1 == INVALID || item_comprovant2 == INVALID)
	{
		printf("Thats a invalid item\n");
		return;
	}

	for (int i = 0; i <= 9; i++)
	{
		for (int j = 0; j <= 9; j++)
		{
			if (_put == item[i]->name && item[i]->inside == true && _into == item[j]->name && item[j]->container == true)
			{
				if (_put == item[1]->name && _into == item[3]->name && item[1]->already_inside == false && item[1]->picked == true && item[3]->picked == true)
				{
					item[3]->chst.push_back(item[1]); //Olyster only can contain pearl
					item[1]->equipped = false;
					item[1]->picked = false;
					item[1]->already_inside = true;
					printf("You put %s into %s\n", item[1]->name.c_str(), item[3]->name.c_str());
					return;
				}

				if (_put == item[5]->name && _into == item[7]->name && item[5]->already_inside == false && item[5]->picked == true && item[7]->picked == true)
				{
					item[7]->chst.push_back(item[5]); //Olyster only can contain pearl
					item[5]->equipped = false;
					item[5]->picked = false;
					item[5]->already_inside = true;
					printf("You put %s into %s\n", item[5]->name.c_str(), item[7]->name.c_str());
					return;
				}

				if (item[5]->name != _put && item[1]->name != _put && item[i]->already_inside == false && item[i]->picked == true && item[j]->picked == true)
				{
					item[j]->chst.push_back(item[i]);
					item[i]->equipped = false;
					item[i]->picked = false;
					item[i]->already_inside = true;
					printf("You put %s into %s\n", item[i]->name.c_str(), item[j]->name.c_str());
					return;
				}
			}
		}

	}

	if (finish == 0)
	{
		printf("You can't put that item inside because It is not his correct place or It already is inside\n");
		return;
	}

}

void Player::Get(const String& _get, const String& _from)
{
	int finish = 0;
	int item_comprovant1 = INVALID;
	int item_comprovant2 = INVALID;
	item_comprovant1 = Item_verification(_get);
	item_comprovant2 = Item_verification(_from);
	if (item_comprovant1 == INVALID || item_comprovant2 == INVALID)
	{
		printf("Thats a invalid item\n");
		return;
	}

	for (int i = 0; i <= 9; i++)
	{
		for (int j = 0; j <= 9; j++)
		{
			if (_get == item[i]->name && item[i]->inside == true && _from == item[j]->name && item[j]->container == true)
			{
				if (_get == item[1]->name && _from == item[3]->name && item[1]->picked == false && item[3]->picked == true && item[1]->already_inside == true)
				{
					item[1]->equipped = false;
					item[1]->picked = true;
					item[1]->already_inside = false;
					printf("You get %s from %s\n", item[1]->name.c_str(), item[3]->name.c_str());
					return;
				}

				if (_get == item[5]->name && _from == item[7]->name && item[5]->already_inside == true && item[5]->picked == false && item[7]->picked == true)
				{
					item[5]->equipped = false;
					item[5]->picked = true;
					item[5]->already_inside = false;
					printf("You get %s from %s\n", item[5]->name.c_str(), item[7]->name.c_str());
					return;
				}

				if (item[5]->name != _get && item[1]->name != _get && item[i]->picked == false && item[j]->picked == true)
				{
					item[j]->chst.push_back(item[i]);
					item[i]->equipped = false;
					item[i]->picked = true;
					item[1]->already_inside = false;
					printf("You get %s from %s\n", item[i]->name.c_str(), item[j]->name.c_str());
					return;
				}
			}
		}

	}

	if (finish == 0)
	{
		printf("You can't get that item from it\n");
		return;
	}

}
*/

Player::~Player()
{}