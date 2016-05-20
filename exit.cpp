#include"world.h"
#include<stdio.h>


Exit::Exit(const char* name, const char* desc, Room* orig, Room* dest, const dir direc, bool clse) 
: Entity(name, desc), origin(orig), destination(dest), direction(direc), close(clse)
{}

Exit::~Exit()
{}