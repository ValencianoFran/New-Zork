#include"world.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INVALID -1
World* world = nullptr;


int main() {
	fflush(stdin);
	world = new World;
	Items item;
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
		
		if (direc != " " && direc != NULL)
		{
			action = direc;
			action.tolower_method();
			int spaces = action.spaces();
			Vector<String> commands = action.Divide(" ", direc);

			if (commands[0] == "quit" || commands[0] == "q")
			{
				break;
			}

			else if (commands[0] == "north" || commands[0] == "n")
			{
				world->player->Go(commands[0]);
			}
			else if(commands[0] == "south" || commands[0] == "s")
			{
				world->player->Go(commands[0]);
			}

			else if(commands[0] == "east" || commands[0] == "e")
			{
				world->player->Go(commands[0]);
			}
			else if(commands[0] == "west" || commands[0] == "w")
			{
				world->player->Go(commands[0]);
			}
			else if(commands[0] == "up" || commands[0] == "u")
			{
				world->player->Go(commands[0]);
			}
			else if(commands[0] == "down" || commands[0] == "d")
			{
				world->player->Go(commands[0]);
			}


			//With 2 words input

			else if (commands.Size() > 1 && (commands[0] == "go" || commands[0] == "g"))
			{
				if (world->player->Direction(commands[1]) != INVALID)
				{
					world->player->Go(commands[1]);
				}
				else
				{
					printf("Thats not a valid direction\n");
				}
			}

			else if (commands[0] == "look" || commands[0] == "l")
			{
				if (spaces == 0)
				{
					world->player->Look(commands[0]);
				}
				else
				{
					world->player->Look(commands[1]);
				}
			}


		
			else if (spaces > 0 && (commands[0] == "open" || commands[0] == "o"))
			{
				world->player->Open(commands[1]);
			}
			else if (spaces > 0 && (commands[0] == "close" || commands[0] == "c"))
			{
			world->player->Close(commands[1]);
			}
			
			//Help
			else if (commands[0] == "help" || commands[0] == "h")
			{
			world->Tutorial();
			}

			else if (commands[0] == "pick")
			{
				world->player->Pick(commands[1]);
			}

			else if (commands[0] == "drop")
			{
				world->player->Drop(commands[1]);
			}
			
			else if (commands[0] == "inventory" || commands[0] == "inv" || commands[0] == "i")
			{
				world->Inventory();
			}

			else if (commands[0] == "equip")
			{
				world->player->Equip(commands[1]);
			}

			else if (commands[0] == "unequip")
			{
				world->player->Unequip(commands[1]);
			}
			
			else if (commands[0] == "put" && commands[2] == "into")
			{
				world->player->Put(commands[1], commands[3]);
			}

			else if (commands[0] == "get" && commands[2] == "from")
			{
				world->player->Get(commands[1], commands[3]);
			}
			//Stats
			else if (commands[0] == "stats")
			{
				world->player->Stats();
			}
			//Attack
			else if (commands[0] == "attack")
			{
				world->player->Attack(commands[1]);

			}

			//If the user introduces invalid command
			else
			{
				printf("I don't understand\n\n");
			}

		}
	}
	return 0;
}

