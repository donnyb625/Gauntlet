#include "Tile.h"


Tile::Tile(TileType tile) : type(tile)
{
}

bool Tile::tick()
{
	return true;
}


void Tile::draw()
{

}

Tile::TileType Tile::getType()
{
	return type;
}
