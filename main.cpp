#include"world.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

World* world = nullptr;

int main() {
	fflush(stdin);
	world = new World;
	String direction("default");
	Vector<String> final_direc;
	char direc[30];

	printf("WELCOME TO MY ZORK!\nYou are lost in one island and you have to scape.\nHave fun!\n\n");
	world->Tutorial(); //Controls
	world->CreateWorld(); //Create the world
	world->CreatePlayer(); //Create player
	printf("Introduce where you want to go:\n");

	while (1)
	{
		gets_s(direc, 30);
		direction = direc;
		final_direc = world->Mayus(direction);
		if (final_direc[0] == "quit" || final_direc[0] == "q")
		{
			break;
		}

		if (final_direc[0] == "north" || final_direc[0] == "n")
		{
			world->player->Go(final_direc[0]);
			break;
		}
		if (final_direc[0] == "south" || final_direc[0] == "s")
		{
			world->player->Go(final_direc[0]);
			return;
		}

		if (final_direc[0] == "east" || final_direc[0] == "e")
		{
			world->player->Go(final_direc[0]);
			return;
		}
		if (final_direc[0] == "west" || final_direc[0] == "w")
		{
			world->player->Go(final_direc[0]);
			return;
		}
		if (final_direc[0] == "up" || final_direc[0] == "u")
		{
			world->player->Go(final_direc[0]);
			return;
		}
		if (final_direc[0] == "down" || final_direc[0] == "d")
		{
			world->player->Go(final_direc[0]);
			return;
		}


		//With 2 words input

		else if (final_direc.Size() > 1 && (final_direc[0] == "go" || final_direc[0] == "g"))
		{
			world->player->Go(final_direc[1]);
			return;
		}

		/*else if (final_direc[0] == "look" || final_direc[0] == "l")
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
		}*/

		else if (final_direc.Size() > 1 && (final_direc[0] == "open" || final_direc[0] == "o"))
		{
			world->player->Open(final_direc[1]);
			return;
		}
		else if (final_direc.Size() > 1 && (final_direc[0] == "close" || final_direc[0] == "c"))
		{
			world->player->Close(final_direc[1]);
			return;
		}

		//Help
		else if (final_direc[0] == "help" || final_direc[0] == "h")
		{
			world->Tutorial();
			return;
		}

		else if (final_direc[0] == "pick")
		{
			world->player->Pick(final_direc[1]);
			return;
		}

		else if (final_direc[0] == "drop")
		{
			world->player->Drop(final_direc[1]);
			return;
		}

		else if (final_direc[0] == "inventory" || final_direc[0] == "inv" || final_direc[0] == "i")
		{
			world->player->Inventory();
			return;
		}

		else if (final_direc[0] == "equip")
		{
			world->player->Equip(final_direc[1]);
			return;
		}

		else if (final_direc[0] == "unequip")
		{
			world->player->Unequip(final_direc[1]);
			return;
		}

		else if (final_direc[0] == "put" && final_direc[2] == "into")
		{
			world->player->Put(final_direc[1], final_direc[3]);
			return;
		}

		else if (final_direc[0] == "get" && final_direc[2] == "from")
		{
			world->player->Get(final_direc[1], final_direc[3]);
			return;
		}

		//If the user introduces invalid action
		else
		{
			printf("I don't understand\n");
		}


	}

	system("pause");
	return 0;
}

