#include"world.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

World* world = nullptr;

int main() {
	fflush(stdin);
	world = new World;
	String action;
	char direc[30];

	printf("WELCOME TO MY ZORK!\nYou are lost in one island and you have to scape.\nHave fun!\n\n");
	world->Tutorial(); //Controls
	world->CreateWorld(); //Create the world
	world->CreatePlayer(); //Create player
	printf("Introduce where you want to go:\n");

	while (1)
	{
		printf("- ");
		gets_s(direc, 30);
		action = direc;
		action.tolower_method();
		Vector<String> commands = action.Divide(" ", direc);
		if (commands[0] == "quit" || commands[0] == "q")
		{
			break;
		}

		if (commands[0] == "north" || commands[0] == "n")
		{
			world->player->Go(commands[0]);
			break;
		}
		if (commands[0] == "south" || commands[0] == "s")
		{
			world->player->Go(commands[0]);
			break;
		}

		if (commands[0] == "east" || commands[0] == "e")
		{
			world->player->Go(commands[0]);
			break;
		}
		if (commands[0] == "west" || commands[0] == "w")
		{
			world->player->Go(commands[0]);
			break;
		}
		if (commands[0] == "up" || commands[0] == "u")
		{
			world->player->Go(commands[0]);
			break;
		}
		if (commands[0] == "down" || commands[0] == "d")
		{
			world->player->Go(commands[0]);
			break;
		}


		//With 2 words input

		else if (commands.Size() > 1 && (commands[0] == "go" || commands[0] == "g"))
		{
			world->player->Go(commands[1]);
			break;
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


		/*
		else if (final_direc.Size() > 1 && (final_direc[0] == "open" || final_direc[0] == "o"))
		{
			world->player->Open(final_direc[1]);
			break;
		}
		else if (final_direc.Size() > 1 && (final_direc[0] == "close" || final_direc[0] == "c"))
		{
			world->player->Close(final_direc[1]);
			break;
		}

		//Help
		else if (final_direc[0] == "help" || final_direc[0] == "h")
		{
			world->Tutorial();
			break;
		}

		else if (final_direc[0] == "pick")
		{
			world->player->Pick(final_direc[1]);
			break;
		}

		else if (final_direc[0] == "drop")
		{
			world->player->Drop(final_direc[1]);
			break;
		}

		else if (final_direc[0] == "inventory" || final_direc[0] == "inv" || final_direc[0] == "i")
		{
			world->player->Inventory();
			break;
		}

		else if (final_direc[0] == "equip")
		{
			world->player->Equip(final_direc[1]);
			break;
		}

		else if (final_direc[0] == "unequip")
		{
			world->player->Unequip(final_direc[1]);
			break;
		}

		else if (final_direc[0] == "put" && final_direc[2] == "into")
		{
			world->player->Put(final_direc[1], final_direc[3]);
			break;
		}

		else if (final_direc[0] == "get" && final_direc[2] == "from")
		{
			world->player->Get(final_direc[1], final_direc[3]);
			break;
		}
		*/
		//If the user introduces invalid action
		else
		{
			printf("I don't understand\n\n");
		}


	}

	return 0;
}

