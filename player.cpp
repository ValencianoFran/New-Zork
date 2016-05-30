#include "world.h"
#include "dlist.h"
#include "creatures.h"
#include "room.h"
#include <stdio.h>
#include <stdlib.h>

#define INVALID -1

Player::Player(const char* name, const char* description, Room* pos, int hp, int dmg,  int money,  bool state, Shape shape) : Creatures(name, description, pos, hp, dmg, money, state, shape)//hp(hp), damage(dmg), position(pos)
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
	bool done = false;
	int direction = Direction(op); //Translate String into enum

		for (i = 0; i < world->entity.Size(); i++)
		{
			if ((world->entity[i]->shape == EXIT && ((Exit*)world->entity[i])->origin == this->place))
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
						Dlist<Entity*>::Node* mylist = list.first;
						while (mylist != nullptr && done == false)
						{
							if (mylist->data->name == "Banana" && ((Creatures*)world->entity[36])->place == place)
							{
								printf("Monkey follows you\n");
								((Creatures*)world->entity[36])->place = ((Exit*)world->entity[i])->destination;	
							}
							if (mylist->data->name == "Guitar" && ((Creatures*)world->entity[36])->place == place)
							{
								printf("Monkey follows you\n");
								((Creatures*)world->entity[36])->place = ((Exit*)world->entity[i])->destination;
							}
							if (((Creatures*)world->entity[36])->place == ((Creatures*)world->entity[37])->place)
							{
								printf("Explorer:\n");
								printf("OH AMANCIO!!\nThank you so much, take this pearl\n");
								((Creatures*)world->entity[37])->money = 0;
								list.push_back(world->entity[26]);
								list.erase(mylist);
								done = true;
							}
							mylist = mylist->next;
						}
						this->place = ((Exit*)world->entity[i])->destination;
						printf("\nYou are in %s\n\n%s \n", this->place->name.c_str(), this->place->description.c_str());
						for (int j = ITEM_VEC; j < world->entity.Size(); j++)
						{
							if (((Creatures*)world->entity[j])->place == place && ((Creatures*)world->entity[j])->hp > 0 && ((Creatures*)world->entity[j])->name != "Lost")
							{
								printf("You can see: %s\t%s\n", ((Creatures*)world->entity[j])->name.c_str(), ((Creatures*)world->entity[j])->description.c_str());
							}
						}
						
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
	int i = 0, saw_items = 0;
	int j = 0;
	bool finish = false;   //Check if go action is completed
	item = Item_verification(op); //Look if the item name is valid

	if (op == "look" || op == "l")
	{
		printf("\nYou see %s\n%s ", place->name.c_str(), place->description.c_str());
		for (int j = ITEM_VEC; j < world->entity.Size(); j++)
		{
			if (((Creatures*)world->entity[j])->place == place && ((Creatures*)world->entity[j])->hp > 0 && ((Creatures*)world->entity[j])->name != "Lost")
			{
				printf("You can see: %s\t%s\n", ((Creatures*)world->entity[j])->name.c_str(), ((Creatures*)world->entity[j])->description.c_str());
			}
		}

		for (j = 0; j < world->entity.Size(); j++)
		{
			if (world->entity[j]->shape == ITEM && ((Items*)world->entity[j])->place == place && ((Items*)world->entity[j])->picked == false && ((Items*)world->entity[j])->equipped == false && ((Items*)world->entity[j])->already_inside == false)
			{
				printf("You can see: %s:\t%s\n", ((Items*)world->entity[j])->name.c_str(), ((Items*)world->entity[j])->description.c_str());
				saw_items++;
			}
		}
		if (saw_items == 0)
		{
			printf("There are no items here\n");
			finish = true;
			return;
		}
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
			if (world->entity[i]->shape == EXIT && ((Exit*)world->entity[i])->origin == place) //Compares the player position with the origin room of the exit
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
	//Returns item damage
	for (int j = ITEM_VEC; j < world->entity.Size(); j++)
	{
		if (((Items*)world->entity[j])->name == item)
		{
			return ((Items*)world->entity[j])->item_damage;
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

			if (((Exit*)world->entity[i])->origin == place) //Compares the player position with the origin room of the exit
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
			if (((Exit*)world->entity[i])->origin == place)
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

void Player::Pick(const String& item)
{
	int i = ITEM_VEC;
	int item_comprovant = INVALID;
	int j = ITEM_VEC;
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

	for (i = ITEM_VEC; ((Items*)world->entity[i])->name != item && i <= world->entity.Size(); i++) //Use i value to know if the item is in a container
	{}

	if (place->list.first != nullptr)
	{
		Dlist<Entity*>::Node* mylist = place->list.first;
		for (; mylist != nullptr; mylist = mylist->next)
		{
			if (mylist->data->name == item)
			{
				if (((Items*)world->entity[i])->already_inside == true)
				{
					printf("That item is inside another one\n");
					return;
				}
				printf("You picked %s\n", mylist->data->name.c_str());
				list.push_back(mylist->data);
				place->list.erase(mylist);
				num_items++;
				return;
			}
		}
	}
	printf("That item is not here or some NPC got it\n");
	return;
}

void Player::Drop(const String& item)
{
	int item_comprovant = INVALID;
	int j = ITEM_VEC;
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


	if (list.first != nullptr)
	{
		Dlist<Entity*>::Node* mylist = list.first;
		for (; mylist != nullptr; mylist = mylist->next)
		{
			if (mylist->data->name == item)
			{
				Unequip(item);
				printf("You dropped %s\n", mylist->data->name.c_str());
				place->list.push_back(mylist->data);
				list.erase(mylist);
				num_items--;
				return;
			}
		}
	}

	printf("You dont have that item in your inventary or It's equipped\n");
	return;
}

void Player::Equip(const String& item)
{
	int item_comprovant = INVALID; 
	int j = ITEM_VEC;
	int this_item = 0;
	bool done = false;
	item_comprovant = Item_verification(item); // RETURNS THE DAMAGE THAT THIS OBJET INCREASES TO THE PLAYER AND SEE IF THE OBJECT EXIST
	if (item_comprovant == INVALID)
	{
		printf("Thats a invalid item\n");
		return;
	}
	
	while (j < world->entity.Size() && done == false)
	{
		if (((Items*)world->entity[j])->name == item)
		{
			this_item = j;
			done = true;
		}
		j++;
	}

	Dlist<Entity*>::Node* mylist = list.first;
	for (; mylist != nullptr; mylist = mylist->next)
	{
		if (mylist->data->name == item)
		{
			if (((Items*)world->entity[this_item])->slot == Hand && hand == false)
			{
				printf("You equiped %s\n", mylist->data->name.c_str());
				hand = true;
				damage += item_comprovant;
				((Items*)world->entity[this_item])->equipped = true;
				return;
			}
			if (((Items*)world->entity[this_item])->slot == Head && head == false)
			{
				printf("You equiped %s\n", mylist->data->name.c_str());
				head = true;
				((Items*)world->entity[this_item])->equipped = true;
				((Room*)world->entity[1])->item_required = false;
				return;
			}
			if (((Items*)world->entity[this_item])->slot == Drive && drive == false)
			{
				printf("You equiped %s\n", mylist->data->name.c_str());
				drive = true;
				((Items*)world->entity[this_item])->equipped = true;
				((Room*)world->entity[2])->item_required = false;
				return;
			}
		}

		else
		{
			if (((Items*)world->entity[this_item])->slot == Hand && hand == true)
			{
				printf("Your hand is actually equiped\n");
				return;
			}
			if (((Items*)world->entity[this_item])->slot == Head && head == true)
			{
				printf("Your head is actually equiped\n");
				return;
			}
			if (((Items*)world->entity[this_item])->slot == Drive && drive == true)
			{
				printf("You already have transport\n");
				return;
			}
		}
	}
}

void Player::Unequip(const String& item)
{

	int item_comprovant = INVALID;
	int this_item = 0;
	bool done = false;
	int j = ITEM_VEC;
	item_comprovant = Item_verification(item);
	if (item_comprovant == INVALID)
	{
		printf("Thats a invalid item\n");
		return;
	}

	while (j < world->entity.Size() && done == false)
	{
		if (((Items*)world->entity[j])->name == item)
		{
			this_item = j;
			done = true;
		}
		j++;
	}


	Dlist<Entity*>::Node* mylist = list.first;
	for (; mylist != nullptr; mylist = mylist->next)
	{
		if (mylist->data->name == item)
		{
			if (((Items*)world->entity[this_item])->slot == Hand && hand == true)
			{
				printf("You unequiped %s\n", mylist->data->name.c_str());
				hand = false;
				damage -= item_comprovant;
				return;
			}
			if (((Items*)world->entity[this_item])->slot == Head && head == true)
			{
				printf("You unequiped %s\n", mylist->data->name.c_str());
				head = false;
				((Items*)world->entity[this_item])->equipped = false;
				((Room*)world->entity[1])->item_required = true;
				return;
			}
			if (((Items*)world->entity[this_item])->slot == Drive && drive == true)
			{
				printf("You unequiped %s\n", mylist->data->name.c_str());
				drive = false;
				((Items*)world->entity[this_item])->equipped = false;
				((Room*)world->entity[2])->item_required = true;
				return;
			}
		}

		else
		{
			if (((Items*)world->entity[this_item])->slot == Hand && hand == false)
			{
				printf("Your hand isn't actually equiped\n");
				return;
			}
			if (((Items*)world->entity[this_item])->slot == Head && head == false)
			{
				printf("Your head isn't actually equiped\n");
				return;
			}
			if (((Items*)world->entity[this_item])->slot == Drive && drive == false)
			{
				printf("You don't have transport\n");
				return;
			}
		}
	}
}

void Player::Put(const String& put, const String& into)
{
	bool finish = false;
	int item_comprovant1 = INVALID;
	int item_comprovant2 = INVALID;
	item_comprovant1 = Item_verification(put);
	item_comprovant2 = Item_verification(into);
	if (item_comprovant1 == INVALID || item_comprovant2 == INVALID)
	{
		printf("Thats a invalid item\n");
		return;
	}


	for (int i = ITEM_VEC; i <= world->entity.Size(); i++)
	{
		if (((Items*)world->entity[i])->name == into)
		{
			Dlist<Entity*>::Node* mylist = list.first;
			for (; mylist != nullptr; mylist = mylist->next)
			{
				if (mylist->data->name == put)
				{
					printf("You put %s into %s\n", mylist->data->name.c_str(), ((Items*)world->entity[i])->name.c_str());
					((Items*)world->entity[i])->list.push_back(mylist->data);
					list.erase(mylist);
					return;
				}
			}
		}
		
	}


	/*for (int i = ITEM_VEC; i <= world->entity.Size(); i++)
	{
		for (int j = ITEM_VEC; j <= world->entity.Size(); j++)
		{
			if (put == ((Items*)world->entity[i])->name && ((Items*)world->entity[i])->inside == true && into == ((Items*)world->entity[j])->name && ((Items*)world->entity[j])->container == true && ((Items*)world->entity[i])->already_inside == false)
			{
				((Items*)world->entity[j])->chest.push_back(((Items*)world->entity[i]));
				((Items*)world->entity[i])->equipped = false;
				((Items*)world->entity[i])->picked = false;
				((Items*)world->entity[i])->already_inside = true;
				printf("You put %s into %s\n", ((Items*)world->entity[i])->name.c_str(), ((Items*)world->entity[j])->name.c_str());
				Drop(put);
				finish = true;
				return;
			}
		}
	}*/

	if (finish == false)
	{
		printf("You can't put that item inside because It is not his correct place or It is already inside\n");
		return;
	}

}

void Player::Get(const String& get, const String& from)
{
	int item_comprovant1 = INVALID;
	int item_comprovant2 = INVALID;
	item_comprovant1 = Item_verification(get);
	item_comprovant2 = Item_verification(from);
	if (item_comprovant1 == INVALID || item_comprovant2 == INVALID)
	{
		printf("Thats a invalid item\n");
		return;
	}
	

	for (int i = ITEM_VEC; i <= world->entity.Size(); i++)
	{
		Dlist<Entity*>::Node* objectlist = ((Items*)world->entity[i])->list.first;
		for (; objectlist != nullptr; objectlist = objectlist->next)
		{
			if (objectlist->data->name == get)
			{
				printf("You get %s from %s\n", objectlist->data->name.c_str(), ((Items*)world->entity[i])->name.c_str());
				list.push_back(objectlist->data);
				((Items*)world->entity[i])->list.erase(objectlist);
				return;
			}
		}
	}

	
	/*for (int i = ITEM_VEC; i <= world->entity.Size(); i++)
	{
		for (int j = ITEM_VEC; j <= world->entity.Size(); j++)
		{
			if (get == ((Items*)world->entity[i])->name && ((Items*)world->entity[i])->inside == true && from == ((Items*)world->entity[j])->name && ((Items*)world->entity[j])->container == true && ((Items*)world->entity[i])->already_inside == true && ((Items*)world->entity[j])->picked == true)
			{
				if (((Items*)world->entity[i])->place == position)
				{
					((Items*)world->entity[j])->chest.pop_back();
					((Items*)world->entity[i])->equipped = false;
					((Items*)world->entity[i])->picked = true;
					((Items*)world->entity[i])->already_inside = false;
					printf("You get %s from %s\n", ((Items*)world->entity[i])->name.c_str(), ((Items*)world->entity[j])->name.c_str());
					return;
				}
				
			}
		}

	}*/

	printf("You can't get that item from it\n");
	return;

}

int Player::Creature_verification(const String& creature)
{
	//Returns HP of the creature
	for (int j = ITEM_VEC; j < world->entity.Size(); j++)
	{
		if (((Creatures*)world->entity[j])->name == creature)
		{
			return ((Creatures*)world->entity[j])->hp;
		}
	}
	return INVALID;
}

void Player::Attack(const String& creature)
{
	int i = ITEM_VEC;
	int creature_comprovant = INVALID;
	int this_creature = 0;
	int creature_room = INVALID;
	int j = 0;
	bool done = false;
	creature_comprovant = Creature_verification(creature);

	if (creature_comprovant == INVALID)
	{
		printf("Thats not a creature\n");
		return;
	}

	while (j < world->entity.Size() && done == false)
	{
		if (((Creatures*)world->entity[j])->name == creature)
		{
			this_creature = j;
			done = true;
		}
		j++;
	}
	

	if (((Creatures*)world->entity[this_creature])->place != place)
	{		
		printf("The creature is not here\n");
		return;
	}

	if (((Creatures*)world->entity[this_creature])->hp > 0)
	{
		printf("You attacked %s and deal %i damage\n", creature, damage);
		((Creatures*)world->entity[this_creature])->hp -= damage;
		if (((Creatures*)world->entity[this_creature])->hp > 0 && ((Creatures*)world->entity[this_creature])->state_agressive == false)
		{
			printf("%s seems agressive now\n", ((Creatures*)world->entity[this_creature])->name.c_str());
			((Creatures*)world->entity[this_creature])->state_agressive = true;
		}
		
		if (((Creatures*)world->entity[this_creature])->hp <= 0)
		{
			printf("You killed %s\n", creature);
			printf("Creature items has been drop on the floor\n");
			if (world->entity[this_creature]->list.first != nullptr)
			{
				Dlist<Entity*>::Node* npc_objects = world->entity[this_creature]->list.first;
				((Creatures*)world->entity[this_creature])->place->list.push_back(npc_objects->data);
				((Creatures*)world->entity[this_creature])->list.pop_front();
			}
			return;
		}
	}
	
	return;
}

void Player::Buy(const String& item, const String& npc)
{
	int item_comprovant = INVALID;
	int this_item = 0;
	item_comprovant = Item_verification(item); // RETURNS THE DAMAGE THAT THIS OBJET INCREASES TO THE PLAYER AND SEE IF THE OBJECT EXIST
	if (item_comprovant == INVALID)
	{
		printf("Thats a invalid item\n");
		return;
	}

	int i = ITEM_VEC;
	int creature_comprovant = INVALID;
	int this_creature = 0;
	creature_comprovant = Creature_verification(npc);

	if (creature_comprovant == INVALID)
	{
		printf("Thats not a npc\n");
		return;
	}

	if (place != ((Creatures*)world->entity[38])->place)
	{
		printf("There are noone to trade with\n");
		return;
	}

	bool finished = false;
	Dlist<Entity*>::Node* mylist = list.first;
	Dlist<Entity*>::Node* npc_objects = world->entity[38]->list.first;
	for (; mylist != nullptr; mylist = mylist->next)
	{
		if (mylist->data->name == "Pearl")
		{
			for (; npc_objects != nullptr; npc_objects = npc_objects->next)
			{
				if (npc_objects->data->name == item)
				{
					printf("You bought %s from %s\n", npc_objects->data->name.c_str(), npc.c_str());
					list.push_back(npc_objects->data);
					world->entity[38]->list.erase(npc_objects);
					world->entity[38]->list.push_back(mylist->data);
					list.erase(mylist);
					return;
				}
			}
		}
		finished = true;
	}

	printf("You don't have pearls to trade\n");
	return;

}

void Player::Sell(const String& item, const String& npc)
{
	int item_comprovant = INVALID;
	int this_item = 0;
	item_comprovant = Item_verification(item); // RETURNS THE DAMAGE THAT THIS OBJET INCREASES TO THE PLAYER AND SEE IF THE OBJECT EXIST
	if (item_comprovant == INVALID)
	{
		printf("Thats a invalid item\n");
		return;
	}

	int i = ITEM_VEC;
	int creature_comprovant = INVALID;
	int this_creature = 0;
	creature_comprovant = Item_verification(npc);

	if (creature_comprovant == INVALID)
	{
		printf("Thats not a npc\n");
		return;
	}

	if (place != ((Creatures*)world->entity[38])->place)
	{
		printf("There are noone to trade with\n");
		return;
	}

	bool finished = false;
	Dlist<Entity*>::Node* mylist = list.first;
	for (; mylist != nullptr; mylist = mylist->next)
	{
		if (mylist->data->name == item && ((Creatures*)world->entity[38])->money > 0)
		{
			printf("You sell %s to %s\n", item.c_str(), npc.c_str());
			world->entity[38]->list.push_back(mylist->data);
			list.erase(mylist);
			((Creatures*)world->entity[38])->money--;
			list.push_back(world->entity[26]); //Adds one pearl to the inventory
			return;

		}
		finished = true;
	}

	printf("You don't have pearls to trade\n");
	return;

}

void Player::Buy_list(const String& creature)
{
	int creature_comprovant = INVALID;
	int this_creature = 0;
	creature_comprovant = Creature_verification(creature);

	if (creature_comprovant == INVALID)
	{
		printf("Thats not a npc\n");
		return;
	}

	if (place != ((Creatures*)world->entity[38])->place)
	{
		printf("There are noone to trade with\n");
		return;
	}

	Dlist<Entity*>::Node* npc_objects = world->entity[38]->list.first;
	for (; npc_objects != nullptr; npc_objects = npc_objects->next)
	{
		printf("%s have %s to sell\n", ((Creatures*)world->entity[38])->name.c_str(), npc_objects->data->name.c_str());
	}
	return;

}

void Player::Talk(const String& creature)
{
	int i = ITEM_VEC;
	int creature_comprovant = INVALID;
	int this_creature = 0;
	int j = 0;
	bool done = false;
	char op = '0';
	creature_comprovant = Creature_verification(creature);

	if (creature_comprovant == INVALID)
	{
		printf("Thats not a creature\n");
		return;
	}

	while (j < world->entity.Size() && done == false)
	{
		if (((Creatures*)world->entity[j])->name == creature)
		{
			this_creature = j;
			done = true;
		}
		j++;
	}

	if (((Creatures*)world->entity[this_creature])->place != place)
	{
		printf("The creature is not here\n");
		return;
	}

	if (((Creatures*)world->entity[this_creature])->hp > 0)
	{
		done = false;
		if (((Creatures*)world->entity[this_creature])->name == "Shopman")
		{
			printf("Shopman:\n");
			printf("Hello!!\nI have some items that can be useful to run out of this island and kill the sharks.\nI have:\n");
			Buy_list(creature);
		}
		if (((Creatures*)world->entity[this_creature])->name == "Explorer")
		{
			printf("Explorer:\n");
			printf("Hello!!\nI've lost my friend Amancio, He is a monkey.\nIf you help me to find him I will give you some money.\nPlease hurry up!!:\n");
			printf("What do you tell me? Will you help me?\n");
			printf("1) Yes! I will bring him back\n");
			printf("2) No, people in this island are mad\n");
			while (done != true)
			{
				printf("- ");
				scanf_s("%c", &op);
				switch (op)
				{
				case '1':
				{
					printf("Explorer:\n");
					printf("Thank you so much, take this guitar, He loves it and maybe will help you to bring him here!\n");
					done = true;
					fflush(stdin);
					break;
				}
				case '2':
				{
					printf("Explorer:\n");
					printf("Ok, I hope you get killed by sharks :)\n");
					done = true;
					fflush(stdin);
					break;
				}
				default:
					printf("Invalid option\n");
					fflush(stdin);
					break;
				}
			}
			
		}
		if (((Creatures*)world->entity[this_creature])->name == "Monkey")
		{
			printf("Monkey:\n");
			printf("Uhuhuhuhuhuhu!!! HuuUUUUUUUUA!\n");
		}
	}
}

Player::~Player()
{}