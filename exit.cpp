#include"world.h"
#include<stdio.h>


Exit::Exit(const char* name, const char* desc, Room* orig, Room* dest, const dir direc, bool close, Shape shape)
: Entity(name, desc, shape), origin(orig), destination(dest), direction(direc), close(close)
{}

Exit::~Exit()
{}