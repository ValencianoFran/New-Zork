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
}



void World::CreateWorld()
{
	/*  -- Room name and description --   */

	// Entity 0
	entity.push_back(new Room("Shore", "You are in a shore, you can try to do snorquel going down, or explore others directions\n", ROOM, false));
	
	// Entity 1
	entity.push_back(new Room("Depths", "It seems to be a pearl inside the oyster\n", ROOM, true));
	
	// Entity 2
	entity.push_back(new Room("Sea", "There are sharks!! I will try to come here later with something to kill them\n", ROOM, true));

	// Entity 3
	entity.push_back(new Room("Palmtrees Island", "Wow there are a lot of palmtrees, it seems that there are something on that one on the east\n", ROOM, false));

	// Entity 4
	entity.push_back(new Room("Palmtree", "There are a monkey! what should i do now?", ROOM, false));

	// Entity 5
	entity.push_back(new Room("Outside house", "I can see a cool house in south, but the door is closed\n", ROOM, false));

	// Entity 6
	entity.push_back(new Room("House", "This house is so extravagant\nThere's a man\n", ROOM, false));

	// Entity 7
	entity.push_back(new Room("Shop", "Maybe i should buy something to kill the sharks and leave this islands.\nThere are something down stairs\n", ROOM, false));

	// Entity 8
	entity.push_back(new Room("Store", "Here is the inventory of the shop, I could catch something borrowed", ROOM, false));


	/*  -- EXITS --    */

	//Entity 9
	entity.push_back(new Exit("Palmtrees Island\n", "There are a lot of trees, seems interesting\n", (Room*)entity[0], (Room*)entity[3], north, false, EXIT));

	//Entity 10
	entity.push_back(new Exit("Shore\n", "There is where I begin this adventure, i should try to do snorquel\n", (Room*)entity[3], (Room*)entity[0], south, false, EXIT));

	//Entity 11
	entity.push_back(new Exit("Palmtree\n", "Maybe there are something in the top of that palmtree\n", (Room*)entity[3], (Room*)entity[4], east, false, EXIT));

	//Entity 12
	entity.push_back(new Exit("Palmtrees Island\n", "There are a lot of trees, seems interesting\n", (Room*)entity[4], (Room*)entity[3], west, false, EXIT));

	//Entity 13
	entity.push_back(new Exit("Sea\n", "There are a sea, seems dangerous\n", (Room*)entity[0], (Room*)entity[2], west, false, EXIT));

	//Entity 14
	entity.push_back(new Exit("Shore\n", "There is where I begin this adventure, i should try to do snorquel\n", (Room*)entity[2], (Room*)entity[0], east, false, EXIT));

	//Entity 15
	entity.push_back(new Exit("Depths\n", "It seems deep\n", (Room*)entity[0], (Room*)entity[1], down, false, EXIT));

	//Entity 16
	entity.push_back(new Exit("Shore\n", "There is where I begin this adventure, i should try to do snorquel\n", (Room*)entity[1], (Room*)entity[0], up, false, EXIT));

	//Entity 17
	entity.push_back(new Exit("Outside House\n", "There are a pretty garden, i should take a look\n", (Room*)entity[0], (Room*)entity[5], east, false, EXIT));

	//Entity 18
	entity.push_back(new Exit("Shore\n", "There is where I begin this adventure, i should try to do snorquel\n", (Room*)entity[5], (Room*)entity[0], west, false, EXIT));

	//Entity 19
	entity.push_back(new Exit("Shop\n", "There must be interesting things to buy\n", (Room*)entity[0], (Room*)entity[7], south, false, EXIT));

	//Entity 20
	entity.push_back(new Exit("Shore\n", "There is where I begin this adventure, i should try to do snorquel\n", (Room*)entity[7], (Room*)entity[0], north, false, EXIT));

	//Entity 21
	entity.push_back(new Exit("Store\n", "What would be down stairs?\n", (Room*)entity[7], (Room*)entity[8], down, false, EXIT));

	//Entity 22
	entity.push_back(new Exit("Shop\n", "There must be interesting things to buy\n", (Room*)entity[8], (Room*)entity[7], up, false, EXIT));

	//Entity 23
	entity.push_back(new Exit("House\n", "There is a pretty garden!\n", (Room*)entity[5], (Room*)entity[6], south, true, EXIT));

	//Entity 24
	entity.push_back(new Exit("Outside House\n", "\n", (Room*)entity[6], (Room*)entity[5], north, false, EXIT));


	//ITEMS

	//Entity 25
	entity.push_back(new Items("Guitar", "You can use this object to attract the monkey\n", (Room*)entity[6], 10, 20, Hand, false, false, false, ITEM));
	//Is with the exploder
	
	//Entity 26
	entity.push_back(new Items("Pearl", "It seems very expensive\n", (Room*)entity[1], 10, 0, Cant_Equip, false, true, true, ITEM));
	entity[1]->list.push_back(entity[26]);
	
	//Entity 27
	entity.push_back(new Items("Harpoon", "It seems powerful and dangerous\n", (Room*)entity[7], 10, 100, Hand, false, false, false, ITEM));
	//Is with the Shopman (entity 38)

	//Entity 28
	entity.push_back(new Items("Oyster", "Maybe constains something with value inside\n", (Room*)entity[1], 10, 0, Cant_Equip, true, false, false, ITEM));
	entity[1]->list.push_back(entity[28]);
	
	//Entity 29
	entity.push_back(new Items("Goggles", "This should allow me to snorquel\n", (Room*)entity[6], 10, 0, Head, false, true, true, ITEM));
	entity[6]->list.push_back(entity[29]);
	
	//Entity 30
	entity.push_back(new Items("Knife", "It cuts, should be careful\n", (Room*)entity[8], 10, 60, Hand, false, true, true, ITEM));
	entity[8]->list.push_back(entity[30]);
	
	//Entity 31
	entity.push_back(new Items("Banana", "It doesn't smell good\n", (Room*)entity[8], 10, 0, Hand, false, false, false, ITEM));
	entity[8]->list.push_back(entity[31]);
	
	//Entity 32
	entity.push_back(new Items("Chest", "There are a knife inside it\n", (Room*)entity[8], 10, 0, Cant_Equip, true, false, false, ITEM));
	entity[8]->list.push_back(entity[32]);
	
	//Entity 33
	entity.push_back(new Items("Box", "There are goggles inside\n", (Room*)entity[6], 10, 0, Cant_Equip, true, false, false, ITEM));
	entity[6]->list.push_back(entity[33]);
	
	//Entity 34
	entity.push_back(new Items("Boat", "It allows you to navegate in the sea\n", (Room*)entity[0], 10, 0, Drive, false, false, false, ITEM));
	entity[0]->list.push_back(entity[34]);

	//Entity 35
	entity.push_back(new Creatures("Shark", "He have big teeths\n", (Room*)entity[2], 50, 100, 0, true, CREATURE));
	
	//Entity 36
	entity.push_back(new Creatures("Monkey", "Seems friendly\n", (Room*)entity[4], 10, 20, 0, true, CREATURE));
	
	//Entity 37
	entity.push_back(new Creatures("Explorer", "He seems interesting\n", (Room*)entity[6], 10, 20, 1, false, NPCS));
	entity[37]->list.push_back(entity[25]);
	
	//Entity 38
	entity.push_back(new Creatures("Shopman", "He will trade for pearls\n", (Room*)entity[7], 10, 20, 0, false, NPCS));
	entity[38]->list.push_back(entity[27]);
}


void World::Tutorial() const //Controls of the game
{
	printf("CONTROLS:\n\tYou can use these commands:\n\tgo [direction], look [direction], open/close [direction], help and quit\n\twith these directions:\n\t<north, south, east, west, up, down>\n\t<n, s, e, w, u, d>\n\tPick/Drop <pick, drop>\n\tEquip/Unequip <equip, unequip>\n\tInventory <inventory, inv, i>\n\tput/get <item> into/from <item>\n\n\tDefault action is 'go' if you only introduce the direction.\n");
}

void World::Inventory()
{
	Dlist<Entity*>::Node* mylist = player->list.first;
	printf("You have this items in the inventory:\n");
	for (; mylist != nullptr; mylist = mylist->next)
	{
		printf("%s\t%s\n", mylist->data->name.c_str(), mylist->data->description.c_str());
		return;
	}
	if (mylist == nullptr)
	{
		printf("You don't have items yet\n");
		return;
	}
	return;
}
