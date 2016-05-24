#include "entity.h"


Entity::Entity(){}

Entity::Entity(const char* name, const char* description, const Shape shape) : name(name), description(description), shape(shape)
{}


Entity::~Entity(){}