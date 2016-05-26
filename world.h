#ifndef _WORLD__
#define _WORLD__

#include "room.h"
#include "player.h"
#include "exit.h"
#include "Entity.h"
#include "string.h"
#include "vector.h"
#include "items.h"

class Items;
class Player;

class World : public Entity
{
public:
	Vector<Entity*> entity;
	Player* player;

	World();
	~World();
	void Tutorial() const;
	void CreatePlayer() const;
	void CreateWorld();

};
extern World* world;

#endif