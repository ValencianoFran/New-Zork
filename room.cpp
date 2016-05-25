#include"world.h"
#include<stdio.h>

Room::Room(const char* name, const char* desc, const Shape shape, const bool item_required) : Entity(name, desc, shape), item_required(item_required)
{}

Room::~Room()
{}


