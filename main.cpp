#include"world.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <Windows.h>
#include "conio.h"

#define INVALID -1
#define DELAY 10000
#define COMMANDBUFFER 50
#define SPECIAL_COOLDOWN 20000

World* world = nullptr;

int main() 
{
	fflush(stdin);
	world = new World;
	unsigned int currenttime = 0;
	unsigned int initialtime = 0;
	Items item;
	String action;
	char direc[30];

	printf("WELCOME TO MY ZORK!\nYou are lost in one island and you have to scape.\nHave fun!\n\n");
	world->CreateWorld(); //Create the world
	world->Tutorial(); //Controls
	printf("///////////////////////////////////////////////////////////////////////////////\n\n\n");
	printf("Introduce your action:\n");
	while (1)
	{
		currenttime = GetTickCount();
		if (currenttime >= (initialtime + DELAY) && ((Creatures*)world->entity[36])->state_agressive == false && ((Creatures*)world->entity[36])->hp > 0 && ((Creatures*)world->entity[36])->place != ((Creatures*)world->entity[37])->place)
		{
			((Creatures*)world->entity[36])->Update();
			initialtime = currenttime;
		}

		if (_kbhit())
		{
			fflush(stdin);
			//Lose condition
			if (world->player->hp <= 0)
			{
				printf("You has been killed, you Lost\n");
				system("pause");
				break;
			}
			//Win condition
			if (((Creatures*)world->entity[35])->hp <= 0)
			{
				printf("Congratulations winner!!\n");
				system("pause");
				break;
			}
			printf("- ");
			gets_s(direc, 30);

			if (direc != "" && direc != " " && direc != NULL)
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
				else if (commands[0] == "south" || commands[0] == "s")
				{
					world->player->Go(commands[0]);
				}

				else if (commands[0] == "east" || commands[0] == "e")
				{
					world->player->Go(commands[0]);
				}
				else if (commands[0] == "west" || commands[0] == "w")
				{
					world->player->Go(commands[0]);
				}
				else if (commands[0] == "up" || commands[0] == "u")
				{
					world->player->Go(commands[0]);
				}
				else if (commands[0] == "down" || commands[0] == "d")
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
					if (commands.Size() > 1)
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

				else if (commands.Size() == 2)
				{
					if (commands[0] == "pick")
					{
						world->player->Pick(commands[1]);
					}

					else if (commands[0] == "drop")
					{
						world->player->Drop(commands[1]);
					}

					else if (commands[0] == "equip")
					{
						world->player->Equip(commands[1]);
					}

					else if (commands[0] == "unequip")
					{
						world->player->Unequip(commands[1]);
					}
					else if (commands[0] == "buy")
					{
						world->player->Buy_list(commands[1]);
					}
					else if (commands[0] == "attack")
					{
						world->player->Attack(commands[1]);
					}
					if (commands[0] == "talk")
					{
						world->player->Talk(commands[1]);
					}
				}
				else if (commands.Size() == 4)
				{
					if (commands[0] == "put" && commands[2] == "into")
					{
						world->player->Put(commands[1], commands[3]);
					}

					else if (commands[0] == "get" && commands[2] == "from")
					{
						world->player->Get(commands[1], commands[3]);
					}
					//Buy
					else if (commands[2] == "from" && commands[0] == "buy")
					{
						world->player->Buy(commands[1], commands[3]);
					}


					//Sell
					else if (commands[0] == "sell" && commands[2] == "from")
					{
						world->player->Sell(commands[1], commands[3]);
					}
				}
				//Inventory
				else if (commands[0] == "inventory" || commands[0] == "inv" || commands[0] == "i")
				{
					world->Inventory();
				}
				//Help
				else if (commands[0] == "help" || commands[0] == "h")
				{
					world->Tutorial();
				}
				//Stats
				else if (commands[0] == "stats")
				{
					world->player->Stats();
				}
				//If the user introduces invalid command

				else
				{
					printf("Wrong command\n\n");
				}
				world->Agressive();
			}
		}
	}
	return 0;
}

