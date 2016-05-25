#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <windows.h>
#include"world.h"
#include<stdio.h>
#include<string.h>


#define NUM_EXITS 16


World::World()
{
	player = new Player;
}

World::~World()
{
	
}

void World::CreatePlayer() const
{
	player->position = (Room*)entity[0];
	player->Look();
}



void World::CreateWorld()
{
	/*  -- Room name and description --   */

	// ROOM 0
	entity.push_back(new Room("Shore", "You are in a shore, you can try to do snorquel going down, or explore others directions\n", ROOM, false));
	
	// ROOM 1
	entity.push_back(new Room("Depths", "It seems to be a pearl inside the oyster\n", ROOM, true));
	
	// ROOM 2
	entity.push_back(new Room("Sea", "There are sharks!! I will try to come here later with something to kill them\n", ROOM, true));

	// ROOM 3
	entity.push_back(new Room("Palmtrees Island", "Wow there are a lot of palmtrees, it seems that there are something on that one on the east\n", ROOM, false));

	// ROOM 4
	entity.push_back(new Room("Palmtree", "There are a monkey! what should i do now?", ROOM, false));

	// ROOM 5
	entity.push_back(new Room("Outside house", "I can see a cool house in south, but the door is closed\n", ROOM, false));

	// ROOM 6
	entity.push_back(new Room("House", "This house is so extravagant\nThere's a man\n", ROOM, false));

	// ROOM 7
	entity.push_back(new Room("Shop", "Maybe i should buy something to kill the sharks and leave this islands.\nThere are something down stairs\n", ROOM, false));

	// ROOM 8
	entity.push_back(new Room("Store", "Here is the inventory of the shop, I could catch something borrowed", ROOM, false));


	/*  -- EXITS --    */

	//EXIT 0
	entity.push_back(new Exit("Palmtrees Island\n", "There are a lot of trees, seems interesting\n", (Room*)entity[0], (Room*)entity[3], north, false, EXIT));

	//EXIT 1
	entity.push_back(new Exit("Shore\n", "There is where I begin this adventure, i should try to do snorquel\n", (Room*)entity[3], (Room*)entity[0], south, false, EXIT));

	//EXIT 2
	entity.push_back(new Exit("Palmtree\n", "Maybe there are something in the top of that palmtree\n", (Room*)entity[3], (Room*)entity[4], east, false, EXIT));

	//EXIT 3
	entity.push_back(new Exit("Palmtrees Island\n", "There are a lot of trees, seems interesting\n", (Room*)entity[4], (Room*)entity[3], west, false, EXIT));

	//EXIT 4
	entity.push_back(new Exit("Sea\n", "There are a sea, seems dangerous\n", (Room*)entity[0], (Room*)entity[2], west, false, EXIT));

	//EXIT 5
	entity.push_back(new Exit("Shore\n", "There is where I begin this adventure, i should try to do snorquel\n", (Room*)entity[2], (Room*)entity[0], east, false, EXIT));

	//EXIT 6
	entity.push_back(new Exit("Depths\n", "It seems deep\n", (Room*)entity[0], (Room*)entity[1], down, false, EXIT));

	//EXIT 7
	entity.push_back(new Exit("Shore\n", "There is where I begin this adventure, i should try to do snorquel\n", (Room*)entity[1], (Room*)entity[0], up, false, EXIT));

	//EXIT 8
	entity.push_back(new Exit("Outside House\n", "There are a pretty garden, i should take a look\n", (Room*)entity[0], (Room*)entity[5], east, false, EXIT));

	//EXIT 9
	entity.push_back(new Exit("Shore\n", "There is where I begin this adventure, i should try to do snorquel\n", (Room*)entity[5], (Room*)entity[0], west, false, EXIT));

	//EXIT 10
	entity.push_back(new Exit("Shop\n", "There must be interesting things to buy\n", (Room*)entity[0], (Room*)entity[7], south, false, EXIT));

	//EXIT 11
	entity.push_back(new Exit("Shore\n", "There is where I begin this adventure, i should try to do snorquel\n", (Room*)entity[7], (Room*)entity[0], north, false, EXIT));

	//EXIT 12
	entity.push_back(new Exit("Store\n", "What would be down stairs?\n", (Room*)entity[7], (Room*)entity[8], down, false, EXIT));

	//EXIT 13
	entity.push_back(new Exit("Shop\n", "There must be interesting things to buy\n", (Room*)entity[8], (Room*)entity[7], up, false, EXIT));

	//EXIT 14
	entity.push_back(new Exit("House\n", "There is a pretty garden!\n", (Room*)entity[5], (Room*)entity[6], south, true, EXIT));

	//EXIT 15
	entity.push_back(new Exit("Outside House\n", "\n", (Room*)entity[6], (Room*)entity[5], north, false, EXIT));


	//ITEMS

	entity.push_back(new Items("Guitar", "You can use this object to attract the monkey\n", (Room*)entity[6], 10, 0, Hand, false, false, false, ITEM));
	entity.push_back(new Items("Pearl", "It seems very expensive\n", (Room*)entity[1], 10, 0, Cant_Equip, false, true, true, ITEM));
	entity.push_back(new Items("Harpoon", "It seems powerful and dangerous\n", (Room*)entity[7], 10, 20, Hand, false, false, false, ITEM));
	entity.push_back(new Items("Oyster", "Maybe constains something with value inside\n", (Room*)entity[1], 10, 0, Cant_Equip, true, false, false, ITEM));
	entity.push_back(new Items("Goggles", "This should allow me to snorquel\n", (Room*)entity[6], 10, 0, Head, false, true, true, ITEM));
	entity.push_back(new Items("Knife", "It cuts, should be careful\n", (Room*)entity[8], 10, 20, Hand, false, true, true, ITEM));
	entity.push_back(new Items("Banana", "It doesn't smell good\n", (Room*)entity[8], 10, 0, Hand, false, false, false, ITEM));
	entity.push_back(new Items("Chest", "There are a knife inside it\n", (Room*)entity[8], 10, 0, Cant_Equip, true, false, false, ITEM));
	entity.push_back(new Items("Box", "There are goggles inside\n", (Room*)entity[6], 10, 0, Cant_Equip, true, false, false, ITEM));
	entity.push_back(new Items("Boat", "It allows you to navegate in the sea\n", (Room*)entity[0], 10, 0, Drive, false, false, false, ITEM));

}


Vector<String> World::Mayus(String& str)//Transform capital letters to lowercase and iniciate the loop with Action
{
	str.tolower_method();//transforms in to lowercase
	Vector <String> word;
	int spc = str.spaces();

	if ((spc + 1) == str.lenght())
	{
		printf("Invalid command\n");
		return word;
	}

	if (spc != 0)
	{
		str.TokenizeString(str.c_str(), word); //divide the principal string in to differents strings
	}

	else
	{
		word.push_back(str.c_str());
	}
	
	

	return word;
}

void World::Tutorial() const //Controls of the game
{
	printf("CONTROLS:\n\tYou can use these commands:\n\tgo [direction], look [direction], open/close [direction], help and quit\n\twith these directions:\n\t<north, south, east, west, up, down>\n\t<n, s, e, w, u, d>\n\tPick/Drop <pick, drop>\n\tEquip/Unequip <equip, unequip>\n\tInventory <inventory, inv, i>\n\tput/get <item> into/from <item>\n\n\tDefault action is 'go' if you only introduce the direction.\n");
}


/*
void World::Look(const String& op) //Look the exit
{
	int direc = INVALID;
	int _item = INVALID;
	int  i = 0, j= 0, saw_items=0;
	bool finish = false;   //Check if go action is completed
	_item = Item_verification(op); //Look if the item name is valid
	
	if (op == "look")
	{
		printf("\nYou see %s\n%s ", player->position->name.c_str(), player->position->description.c_str());
		printf("You can see this items:\n");
		for (j = 0; j <= 9; j++)
		{
			if (item[j]->place == player->position && item[j]->picked == false && item[j]->equipped == false && item[j]->already_inside == false)
			{
				item[j]->Look();
				saw_items++;
			}
		}
		if (saw_items == 0) printf("There are no items here\n");
		finish = true;
		return;
	}
	
	direc = Direction(op); //Look if the direction name is valid
	if (direc == INVALID && _item == INVALID)
	{
		printf("Invalid command\n");
		return;
	}

	if (direc != INVALID)
	{
		for (i = 0; i < NUM_EXITS; i++)
		{

			if (exit[i]->origin->name == player->position->name) //Compares the player position with the origin room of the exit
			{
				if (exit[i]->direction == direc)
				{
					printf("\nYou see %s\n%s ", exit[i]->name.c_str(), exit[i]->description.c_str());
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

	if (_item != INVALID)
	{
		for (int j = 0; j <= 9; j++)
		{
			if (item[j]->name == op)
			{
				item[j]->Look();
				return;
			}
		}
	}
}

void World::Open(const String& op) //Open doors
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
		for (i = 0; i < NUM_EXITS; i++)
		{

			if (exit[i]->origin->name == player->position->name) //Compares the player position with the origin room of the exit
			{
				if (exit[i]->direction == direc)
				{
					if (exit[i]->close == true)
					{		// If the door is closed, open it
						exit[i]->close = false;
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

void World::Close(const String& op) //Close doors, same function of Open, but it closes the door
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
		for (i = 0; i < NUM_EXITS; i++)
		{

			if (exit[i]->origin->name == player->position->name)
			{
				if (exit[i]->direction == direc)
				{
					if (exit[i]->close == true)
					{
						exit[i]->close = false;
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
 




void World::Inventory()
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


int World::Item_verification(const String& item_)
{
	for (int j = 0; j <= 9; j++)
	{
		if (item[j]->name == item_)
		{
			return 1;
		}
	}
	return INVALID;
}

void World::Pick(const String& _item)
{
	int item_comprovant = INVALID;
	if (player->num_items >= player->bag_capacity)
	{
		printf("The bag is full\n");
		return;
	}

	item_comprovant = Item_verification(_item);
	if (item_comprovant == INVALID)
	{
		printf("Thats a invalid item\n");
		return;
	}


	for (int j = 0; j <= 9; j++)
	{
		if (item[j]->name == _item && item[j]->place == player->position)
		{
			if (item[j]->picked == false && item[j]->equipped == false && item[j]->already_inside == false)
			{
				item[j]->picked = true;
				printf("You picked %s\n", item[j]->name.c_str());
				return;
			}
			if (item[j]->picked == false && item[j]->equipped == false && item[j]->already_inside == true)
			{
				printf("You must get the item from the container\n");
			}
		}
	}

	printf("You have already picked that item or it isn't here\n");
	return;
}

void World::Drop(const String& _item)
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
			if (item[j]->picked == true && item[j]->equipped == false)
			{
				item[j]->picked = false;
				item[j]->place = player->position;
				printf("You dropped %s\n", item[j]->name.c_str());
				return;
			}
		}
	}

	printf("You dont have that item in your inventary or It's equipped\n");
	return;

}

void World::Equip(const String& _item)
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

void World::Unequip(const String& _item)
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

void World::Put(const String& _put, const String& _into)
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

void World::Get(const String& _get, const String& _from)
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