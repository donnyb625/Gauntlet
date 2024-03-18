#include "Floor.h"


Floor::Floor(int initTotalEntities, Entity** initEntities,
	sf::RenderWindow* initWindow, sf::Color initBG, sf::Color initFG,
	WallStyle initWallStyle, FloorStyle initFloorStyle)
	: window(initWindow), entities(initEntities),
	totalEntities(initTotalEntities), bgColor(initBG), fgColor(initFG),
	wallStyle(initWallStyle), floorStyle(initFloorStyle)
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


void Floor::tick(double& deltatime)
{
	entityTick(deltatime);
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


// Modify to skip ticking player; handled by Game
void Floor::entityTick(double& deltatime)
{
	Player* isPlayer = nullptr;
	Enemy* isEnemy = nullptr;
	Projectile* isProjectile = nullptr;
	TileEntity* isTileEntity = nullptr;
	sf::Sprite toDraw;

	// Will always throw read access violation errors until loading is finished and a level file is made
	for (int i = 0; i < totalEntities; i++)
	{
		isPlayer = dynamic_cast<Player*>(entities[i]);
		isEnemy = dynamic_cast<Enemy*>(entities[i]);
		isProjectile = dynamic_cast<Projectile*>(entities[i]);
		isTileEntity = dynamic_cast<TileEntity*>(entities[i]);

		// Is Player
		if (isPlayer)
		{
			isPlayer->tick(deltatime);
			toDraw = isPlayer->draw();
		}
		else if (isEnemy)
		{
			isEnemy->tick(deltatime);
			toDraw = isEnemy->draw();
		}
		else if (isProjectile)
		{
			isProjectile->tick(deltatime);
			toDraw = isProjectile->draw();
		}
		else if (isTileEntity)
		{
			isTileEntity->tick(deltatime);
			toDraw = isTileEntity->draw();
		}

		window->draw(toDraw);
	}
}
