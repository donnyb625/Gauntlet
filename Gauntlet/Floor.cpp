#include "Floor.h"
#include "invalid_type.h"
#include <cmath> // abs function


Floor::Floor(int initTotalEntities, Entity** initEntities,
		int initTotalTiles, TileRegion* initTiles,
	sf::RenderWindow* initWindow, sf::Color initBG, sf::Color initFG,
	WallStyle initWallStyle, FloorStyle initFloorStyle)
	: window(initWindow), entities(initEntities),
	totalEntities(initTotalEntities), bgColor(initBG), fgColor(initFG),
	wallStyle(initWallStyle), floorStyle(initFloorStyle),
	totalTiles(initTotalTiles)
{
	patternToTiles(initTiles, initTotalTiles);
}

void Floor::patternToTiles(TileRegion* patterns, int size)
{
	for (int i = 0; i < size; i++)
	{
		// Throw an error if it receives a NULL_TYPE tile
		if (patterns[i].tiles.singleTile.getType()
			== Tile::NULL_TYPE)
			throw invalid_type("Tile cannot be 'NULL_TYPE' on floor");

		// Identify the method in which to wtite to the floor
		switch (patterns[i].type)
		{
			// Throw an error if it recieves a NULL_TYPE Region
		case RegionType::NULL_TYPE:
			throw invalid_type("Region cannot be 'NULL_TYPE' on floor");
			break;

		case RegionType::BOX: // will need remaking
			for (int j = 0; j < patterns[i].beta.y - patterns[i].alpha.y; j++)
			{
				for (
					int k = 0;
					k < patterns[i].beta.x - patterns[i].alpha.x;
					k++
				)
				{
					if (j == patterns[i].alpha.y ||
						j == patterns[i].beta.y ||
						k == patterns[i].alpha.x ||
						k == patterns[i].beta.x)
						tiles[j][k] = patterns[i].tiles.singleTile;
				}
			}
			break;

		case RegionType::CHECKERBOARD_ONE:
			patterns[i].tiles.tileArray[1] = Tile(Tile::AIR);

		case RegionType::CHECKERBOARD_TWO_ALTERNATE:
			if (patterns[i].tiles.tileArray[1].getType() == Tile::NULL_TYPE)
				throw invalid_type("Tile cannot be 'NULL_TYPE' on floor");


			for (int j = 0; j < patterns[i].beta.y - patterns[i].alpha.y; j++)
			{
				for (
					int k = 0;
					k < patterns[i].beta.x - patterns[i].alpha.x;
					k++
					)
				{
					if ((j + k) % 2 == 0)
						tiles[j][k] = patterns[i].tiles.tileArray[0];
					else
						tiles[j][k] = patterns[i].tiles.tileArray[1];
				}
			}
			break;

		case RegionType::CHECKERBOARD_TWO_ROW:
			if (patterns[i].tiles.tileArray[1].getType() == Tile::NULL_TYPE)
				throw invalid_type("Tile cannot be 'NULL_TYPE' on floor");


			for (int j = 0; j < patterns[i].beta.y - patterns[i].alpha.y; j++)
			{
				for (
					int k = 0;
					k < patterns[i].beta.x - patterns[i].alpha.x;
					k++
					)
				{
					if (j % 2 == 0)
						tiles[j][k] = patterns[i].tiles.tileArray[0];
					else
						tiles[j][k] = patterns[i].tiles.tileArray[1];
				}
			}

			break;

		case RegionType::DIAGONAL_CONNECTED_OVER:
			{
				int x1 = patterns[i].alpha.x, x2 = patterns[i].beta.x,
					y1 = patterns[i].alpha.y, y2 = patterns[i].beta.y;

				if (!(abs(y1 - y2) == abs(x1 - x2) ||
					 (abs(y1 - y2) == abs(x1 - x2) - 1)))
					throw std::out_of_range(
						"DIAGONAL_CONNECTED_OVER is out of point range!"
					);

				for (int j = 0; j < abs(y1 - y2); j++)
					tiles[y1 + j][x1 + j] = patterns[i].tiles.singleTile;


				for (int j = 0; j < abs(y1 - y2) - 1; j++)
					tiles[y1 + j][x1 + j + 1] = patterns[i].tiles.singleTile;

				if ((abs(y1 - y2) == abs(x1 - x2) - 1))
					tiles[y2][x2] = patterns[i].tiles.singleTile;

			}
			break;

		case RegionType::DIAGONAL_CONNECTED_UNDER:
			{
				int x1 = patterns[i].alpha.x, x2 = patterns[i].beta.x,
					y1 = patterns[i].alpha.y, y2 = patterns[i].beta.y;

				if (!(abs(y1 - y2)     == abs(x1 - x2) ||
					 (abs(y1 - y2) - 1 == abs(x1 - x2))))
					throw std::out_of_range(
						"DIAGONAL_CONNECTED_UNDER is out of point range!"
					);

				for (int j = 0; j < abs(x1 - x2); j++)
					tiles[y1 + j][x1 + j] = patterns[i].tiles.singleTile;

				for (int j = 0; j < abs(x1 - x2) - 1; j++)
					tiles[y1 + j + 1][x1 + j] = patterns[i].tiles.singleTile;

				if ((abs(y1 - y2) == abs(x1 - x2) - 1))
					tiles[y2][x2] = patterns[i].tiles.singleTile;

				break;

				case RegionType::DIAGONAL_DISCONNECTED:
					{
						int x1 = patterns[i].alpha.x, x2 = patterns[i].beta.x,
							y1 = patterns[i].alpha.y, y2 = patterns[i].beta.y;

						if (abs(y1 - y2) != abs(x1 - x2))
							throw std::out_of_range(
								"DIAGONAL_CONNECTED_OVER is out of point range!"
							);

						for (int j = 0; j < abs(y1 - y2); j++)
							tiles[y1 + j][x1 + j] = patterns[i].tiles.singleTile;
					}
				break;

				case RegionType::SOLID:
					for (int j = 0; j < patterns[i].beta.y - patterns[i].alpha.y; j++)
					{
						for (
							int k = 0;
							k < patterns[i].beta.x - patterns[i].alpha.x;
							k++
							)
						{
							tiles[j][k] = patterns[i].tiles.singleTile;
						}
					}
				break;
			}
		}
	}
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
	/*
	 * ###########################
	 * # MAKE MORE ROBUST LOGIC  #
	 * # SEARCH ADJCENT TILES    #
	 * # USE DELETE AND DONT     #
	 * # EXPLICITLY CALL THE     #
	 * # DESTRUCTOR              #
	 * ###########################
	 */
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

	default:
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
