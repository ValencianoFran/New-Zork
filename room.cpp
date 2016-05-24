#include"world.h"
#include<stdio.h>

Room::Room(const char* name, const char* desc, const Shape shape) : Entity(name, desc, shape)
{}

Room::~Room()
{}


