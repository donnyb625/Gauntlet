#include "TileEntity.h"


TileEntity::TileEntity(TileType type, ResourceManager* resManInit,
	BoundsManager* boundManInit) : Entity(resManInit, boundManInit)
{

}


TileEntity::~TileEntity()
{

}

void TileEntity::tick()
{
}

sf::Sprite TileEntity::draw()
{
	return sf::Sprite();
}


void TileEntity::isPoison(TileType type)
{

}


void TileEntity::method(TileType type)
{

}