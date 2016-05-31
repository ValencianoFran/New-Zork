#include "creatures.h"
#include "world.h"
#include <Windows.h>
#include <math.h>
#include "room.h"

Creatures::Creatures(const char* name, const char* description, Room* place, int hp, int dmg, int money, const bool state, Shape shape)
: Entity(name, description, shape), place(place), hp(hp), damage(dmg), money(money), state_agressive(state)
{}

void Creatures::Update()
{
	int random_exit = 9 + rand() % 16;
	Room* prev = ((Creatures*)world->entity[36])->place;
	bool done = false;
	Dlist<Entity*>::Node* mylist = world->player->list.first;
	while (mylist != nullptr)
	{
		if (mylist->data->name == "Banana")
		{
			done = true;
		}
		if (mylist->data->name == "Guitar" && ((Creatures*)world->entity[36])->place == place)
		{
			done = true;
		}
		mylist = mylist->next;
	}

	if (((Creatures*)world->entity[36])->hp > 0 && done == false) //36 == monkey
	{
		while(done == false)
		{
			if ((world->entity[random_exit]->shape == EXIT && ((Exit*)world->entity[random_exit])->origin == ((Creatures*)world->entity[36])->place) && random_exit != 13 && random_exit != 23 && random_exit != 15) //Monkey can't go Depths, Explorer house or sea
			{
				((Creatures*)world->entity[36])->place = ((Exit*)world->entity[random_exit])->destination;
				if (((Creatures*)world->entity[36])->place == world->player->place)
				{
					printf("%s entered the room\n", ((Creatures*)world->entity[36])->name.c_str());
				}
				if (prev == world->player->place)
				{
					printf("%s left this room\n", ((Creatures*)world->entity[36])->name.c_str());
				}
				done = true;
			}
			else
			{
				random_exit = 9 + rand() % 15;
			}
		}
		
	}
}

Creatures::~Creatures()
{}