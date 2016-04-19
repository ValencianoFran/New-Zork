#include"world.h"
#include<stdio.h>


Exit::Exit(const char* _name, const char* _desc, Room* _orig, Room* _dest, const dir _direc, bool _clse) 
: Entity(_name, _desc), origin(_orig), destination(_dest), direction(_direc), close(_clse)
{}

Exit::~Exit()
{}