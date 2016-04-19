#include"world.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



int main() {
	fflush(stdin);
	World world;
	world.CreateWorld(); //Create the world
	String direction("default");
	char direc[30];

	printf("WELCOME TO MY ZORK!\nYou are lost in one island and you have to scape.\nHave fun!\n\n");
	world.Tutorial(); //Controls
	printf("Introduce where you want to go:\n");

	while (1)
	{
		gets_s(direc, 30);
		direction = direc;
		world.Mayus(direction);
		if (direction == "quit")
		{
			break;
		}
	}

	system("pause");
	return 0;
}

