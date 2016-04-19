#ifndef _EXIT__
#define _EXIT__

#include"world.h"
#include"Entity.h"

enum dir
{
	north = 0,
	south,
	east,
	west,
	up,
	down
};

class Exit : public Entity{
public:
	Room* origin;
	Room* destination;
	dir direction;
	bool close = false;
	Exit(const char* _name, const char* _desc, Room* orig, Room* dest, const dir direc, bool clse);
	~Exit();
};


#endif
