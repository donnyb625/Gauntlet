#include "TileEntity.h"


TileEntity::TileEntity(TileType type, ResourceManager* resManInit,
	int x, int y, BoundsManager* boundManInit)
	: Entity(resManInit, boundManInit, sf::Vector2<double>(x,y)),
	type(NULL_TYPE)
{

}


TileEntity::~TileEntity()
{

}

void TileEntity::tick(double deltatime)
{
	if (type == NULL_TYPE)
		throw std::runtime_error("Tile Entity used without being initialized");
}

sf::Sprite TileEntity::draw()
{
	return sf::Sprite();
}


void TileEntity::isPoison(TileType type)
{

}

void TileEntity::loadSprites()
{
}

void TileEntity::loadSounds()
{
}
