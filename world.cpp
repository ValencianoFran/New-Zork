#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <windows.h>
#include"world.h"
#include<stdio.h>
#include<string.h>


#define NUM_EXITS 16
#define INVALID -1

World::World()
{
	player = new Player;
}

World::~World()
{
	
}

void World::CreatePlayer() const
{
	player->position = room[0];
}



void World::CreateWorld()
{
	
	/*  -- Room name and description --   */

	// ROOM 0
	room.push_back(new Room("Shore", "You are in a shore, you can try to do snorquel going down, or explore others directions\n"));
	
	// ROOM 1
	room.push_back(new Room("Depths", "It seems to be a pearl inside the oyster\n"));

	// ROOM 2
	room.push_back(new Room("Sea", "There are sharks!! I will try to come here later with something to kill them\n"));

	// ROOM 3
	room.push_back(new Room("Palmtrees Island", "Wow there are a lot of palmtrees, it seems that there are something on that one on the east\n"));

	// ROOM 4
	room.push_back(new Room("Palmtree", "There are a monkey! what should i do now?"));

	// ROOM 5
	room.push_back(new Room("Outside house", "I can see a cool house in south, but the door is closed\n"));

	// ROOM 6
	room.push_back(new Room("House", "This house is so extravagant\nThere's a man\n"));

	// ROOM 7
	room.push_back(new Room("Shop", "Maybe i should buy something to kill the sharks and leave this islands.\nThere are something down stairs\n"));

	// ROOM 8
	room.push_back(new Room("Store", "Here is the inventory of the shop, I could catch something borrowed"));


	/*  -- EXITS --    */

	//EXIT 0
	exit.push_back(new Exit("Palmtrees Island\n", "There are a lot of trees, seems interesting\n", room[0], room[3], north, false));

	//EXIT 1
	exit.push_back(new Exit("Shore\n", "There is where I begin this adventure, i should try to do snorquel\n", room[3], room[0], south, false));

	//EXIT 2
	exit.push_back(new Exit("Palmtree\n", "Maybe there are something in the top of that palmtree\n", room[3], room[4], east, false));

	//EXIT 3
	exit.push_back(new Exit("Palmtrees Island\n", "There are a lot of trees, seems interesting\n", room [4], room[3], west, false));

	//EXIT 4
	exit.push_back(new Exit("Sea\n", "There are a sea, seems dangerous\n", room[0], room[2], west, false));

	//EXIT 5
	exit.push_back(new Exit("Shore\n", "There is where I begin this adventure, i should try to do snorquel\n", room[2], room[0], east, false));

	//EXIT 6
	exit.push_back(new Exit("Depths\n", "It seems deep\n", room[0], room[1], down, false));

	//EXIT 7
	exit.push_back(new Exit("Shore\n", "There is where I begin this adventure, i should try to do snorquel\n", room[1], room[0], up, false));

	//EXIT 8
	exit.push_back(new Exit("Outside House\n", "There are a pretty garden, i should take a look\n", room[0], room[5], east, false));

	//EXIT 9
	exit.push_back(new Exit("Shore\n", "There is where I begin this adventure, i should try to do snorquel\n", room[5], room[0], west, false));

	//EXIT 10
	exit.push_back(new Exit("Shop\n", "There must be interesting things to buy\n", room[0], room[7], south, false));

	//EXIT 11
	exit.push_back(new Exit("Shore\n", "There is where I begin this adventure, i should try to do snorquel\n", room[7], room[0], north, false));

	//EXIT 12
	exit.push_back(new Exit("Store\n", "What would be down stairs?\n", room[7], room[8], down, false));

	//EXIT 13
	exit.push_back(new Exit("Shop\n", "There must be interesting things to buy\n", room[8], room[7], up, false));

	//EXIT 14
	exit.push_back(new Exit("House\n", "There is a pretty garden!\n", room[5], room[6], south, true));

	//EXIT 15
	exit.push_back(new Exit("Outside House\n", "\n", room[6], room[5], north, false));


	//ITEMS

	item.push_back(new Items("Guitar", "You can use this object to attract the monkey\n", room[6], 10, 0, Hand, false, false, false));
	item.push_back(new Items("Pearl", "It seems very expensive\n", room[1], 10, 0, Cant_Equip, false, true, true));
	item.push_back(new Items("Harpoon", "It seems powerful and dangerous\n", room[7], 10, 20, Hand, false, false, false));
	item.push_back(new Items("Oyster", "Maybe constains something with value inside\n", room[1], 10, 0, Cant_Equip, true, false, false));
	item.push_back(new Items("Goggles", "This should allow me to snorquel\n", room[6], 10, 0, Head, false, true, true));
	item.push_back(new Items("Knife", "It cuts, should be careful\n", room[8], 10, 20, Hand, false, true, true));
	item.push_back(new Items("Banana", "It doesn't smell good\n", room[8], 10, 0, Hand, false, false, false));
	item.push_back(new Items("Chest", "There are a knife inside it\n", room[8], 10, 0, Cant_Equip, true, false, false));
	item.push_back(new Items("Box", "There are goggles inside\n", room[6], 10, 0, Cant_Equip, true, false, false));
	item.push_back(new Items("Boat", "It allows you to navegate in the sea\n", room[0], 10, 0, Drive, false, false, false));

	CreatePlayer();
}


void World::Mayus(String& str)//Transform capital letters to lowercase and iniciate the loop with Action
{
	str.tolower_method();//transforms in to lowercase
	Vector <String> word;
	int spc = str.spaces();

	if ((spc + 1) == str.lenght())
	{
		printf("Invalid command\n");
		return;
	}

	if (spc != 0)
	{
		str.TokenizeString(str.c_str(), word); //divide the principal string in to differents strings
	}

	else
	{
		word.push_back(str.c_str());
	}
	
	

	Action(word, spc);
}

int World::Direction(const String& op) //Check the direction is valid
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


void World::Go(const String& op) //Move player
{
	int direc = INVALID;
	int  i = 0;
	bool finish = false;   //Check if go action is completed
	direc = Direction(op); //Check the direction is valid

	if (direc == INVALID)
	{
		printf("Invalid direction\n\n");
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
					if (exit[i]->destination == room[1] && item[4]->equipped == false)
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
}

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
 
void World::Tutorial() const //Controls of the game
{
	printf("CONTROLS:\n\tYou can use these commands:\n\tgo [direction], look [direction], open/close [direction], help and quit\n\twith these directions:\n\t<north, south, east, west, up, down>\n\t<n, s, e, w, u, d>\n\tPick/Drop <pick, drop>\n\tEquip/Unequip <equip, unequip>\n\tInventory <inventory, inv, i>\n\tput/get <item> into/from <item>\n\n\tDefault action is 'go' if you only introduce the direction.\n");
}


void World::Action(Vector<String> &act, const int& space) //Do the action that the player input
{
	/*With 1 word input*/
	/*Go actions (every 'if' does the same function)*/

	if (act[0] == "north" || act[0] == "n")
	{
		Go(act[0]);
		return;
	}
	if (act[0] == "south" || act[0] == "s")
	{
		Go(act[0]);
		return;
	}

	if (act[0] == "east" || act[0] == "e")
	{
		Go(act[0]);
		return;
	}
	if (act[0] == "west" || act[0] == "w")
	{
		Go(act[0]);
		return;
	}
	if (act[0] == "up" || act[0] == "u")
	{
		Go(act[0]);
		return;
	}
	if (act[0] == "down" || act[0] == "d")
	{
		Go(act[0]);
		return;
	}


	//With 2 words input

	else if (act.Size() > 1 && (act[0] == "go" || act[0] == "g"))
	{
		Go(act[1]);
		return;
	}

	else if (space <= 2 && (act[0] == "look" || act[0] == "l"))
	{
		if (space == 0)
		{
			Look(act[0]);
			return;
		}
		else
		{
			Look(act[1]);
			return;
		}
	}

	else if (act.Size() > 1 && (act[0] == "open" || act[0] == "o"))
	{
		Open(act[1]);
		return;
	}
	else if (act.Size() > 1 && (act[0] == "close" || act[0] == "c"))
	{
		Close(act[1]);
		return;
	}


	//Quit and help
	else if (space >= 0  && act[0] == "quit")
	{
		return;
	}

	else if (act[0] == "help" || act[0] == "h")
	{
		Tutorial();
		return;
	}

	else if (space == 1 && act[0] == "pick")
	{
		Pick(act[1]);
		return;
	}

	else if (space == 1 && act[0] == "drop")
	{
		Drop(act[1]);
		return;
	}

	else if (act[0] == "inventory" || act[0] == "inv" || act[0] == "i")
	{
		Inventory();
		return;
	}

	else if (space == 1 && act[0] == "equip")
	{
		Equip(act[1]);
		return;
	}

	else if (space == 1 && act[0] == "unequip")
	{
		Unequip(act[1]);
		return;
	}

	else if (space == 3 && (act[0] == "put" && act[2] == "into"))
	{
		Put(act[1], act[3]);
		return;
	}

	else if (space == 3 && (act[0] == "get" && act[2] == "from"))
	{
		Get(act[1], act[3]);
		return;
	}



	//If the user introduces invalid action
	else{
		printf("I don't understand\n");
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
				if (item[j]->slot == 0 && player->_head == false)
				{
					item[j]->equipped = true;
					item[j]->picked = false;
					player->_head = true;
					printf("You equiped %s\n", item[j]->name.c_str());
					return;
				}
				if (item[j]->slot == 1 && player->_hand == false)
				{
					item[j]->equipped = true;
					item[j]->picked = false;
					player->_hand = true;
					printf("You equiped %s\n", item[j]->name.c_str());
					return;
				}

				if (item[j]->slot == 3 && player->_drive == false)
				{
					item[j]->equipped = true;
					item[j]->picked = false;
					player->_drive = true;
					printf("You equiped %s\n", item[j]->name.c_str());
					return;
				}
				
			}

			else
			{
				if (item[j]->slot == 0 && player->_head == true)
				{
					printf("Actually your head is equiped\n");
				}
				if (item[j]->slot == 1 && player->_hand == true)
				{
					printf("Actually your hand is equiped\n");
				}
				if (item[j]->slot == 3 && player->_drive == true)
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
				if (item[j]->slot == 0 && player->_head == true)
				{
					item[j]->equipped = false;
					item[j]->picked = true;
					player->_head = false;
					printf("You unequipped %s\n", item[j]->name.c_str());
					return;
				}
				if (item[j]->slot == 1 && player->_hand == true)
				{
					item[j]->equipped = false;
					item[j]->picked = true;
					player->_hand = false;
					printf("You unequipped %s\n", item[j]->name.c_str());
					return;
				}

				if (item[j]->slot == 3 && player->_drive == true)
				{
					item[j]->equipped = false;
					item[j]->picked = true;
					player->_drive = false;
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