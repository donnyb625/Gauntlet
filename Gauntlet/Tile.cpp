#include "Tile.h"


Tile::Tile(TileType tile) : type(tile)
{
}


Tile::~Tile()
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
