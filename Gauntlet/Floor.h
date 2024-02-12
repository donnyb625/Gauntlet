#pragma once
#include "Tile.h"

class Floor
{
public:
	Floor();
	~Floor();
	void draw();
	void tick();

private:
	Tile tiles[];

	void destroyTile();
	void spawnEntity();
};