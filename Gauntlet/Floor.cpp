#include "Floor.h"


Floor::Floor()
{
	  
}


Floor::~Floor()
{

}


//Experimenting with pulling textures from a file
void Floor::draw()
{
	sf::Texture floorTexture;
	floorTexture.loadFromFile("Gauntlet-Level-1.png");

	sf::Sprite floor;

	window->draw(floor);
}


void Floor::tick()
{

}

void Floor::setWindow(sf::RenderWindow& newWindow)
{
	window = &newWindow;
}
  

void Floor::destroyTile(Tile::TileType type, Tile tile)
{
	switch(type) 
	{
		//If the tile is shot by a player, destroy tile
		case Tile::WALL_BREAKABLE:
			tile.~Tile();
			break;

		//If the trigger condition is met, destroy tile
		case Tile::TRAP:
			tile.~Tile();
			break;

		//If the player has a key in their inventory, destroy tile
		case Tile::DOOR:
			tile.~Tile();
			break;
	}
}