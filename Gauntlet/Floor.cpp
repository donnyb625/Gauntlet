#include "Floor.h"
#include "invalid_type.h"
#include <cmath> // abs function
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "TileEntity.h"


Floor::Floor(int initTotalEntities, Entity** initEntities, int totalPlayers,
		int initTotalTiles, TileRegion* initTiles,
	sf::RenderWindow* initWindow, sf::Color initBG, sf::Color initFG,
	WallStyle initWallStyle, FloorStyle initFloorStyle)
	: window(initWindow), entities(initEntities), totalPlayers(totalPlayers),
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

		// Identify the method in which to write to the floor
		switch (patterns[i].type)
		{
			// Throw an error if it receives a NULL_TYPE Region
		case RegionType::NULL_TYPE:
			throw invalid_type("Region cannot be 'NULL_TYPE' on floor");
			break;

		case RegionType::BOX: // Draws a box between two points
			// If the second point is higher than, or to the left of the first
			if (patterns[i].beta.y > patterns[i].alpha.y ||
				patterns[i].beta.x < patterns[i].alpha.x)
				throw std::out_of_range(
					"Pattern is out of point range! Higher or to the left."
			);
			
			// Draws vertical lines
			for (int j = 0; patterns[j].beta.y - patterns[j].alpha.y; j++)
			{
				tiles[j][patterns[j].beta.x] = patterns[j].tiles.singleTile;
				tiles[j][patterns[j].alpha.x] = patterns[j].tiles.singleTile;
			}
			// draws horizontal lines
			for (int j = 0; patterns[j].beta.x - patterns[j].alpha.x; j++)
			{
				tiles[j][patterns[j].beta.y] = patterns[j].tiles.singleTile;
				tiles[j][patterns[j].alpha.y] = patterns[j].tiles.singleTile;
			}
			break;

		/*
		 * The CHECKERBOARD_ONE and CHECKERBOARD_TWO_ALTERNATE
		 * patterns define a checkerboard like pattern on the
		 * floor when drawing and the difference between the two
		 * is that CHECKERBOARD_ONE will have the second tile
		 * defined a AIR since it generates the same output, just
		 * with the second tile as air, hence the fall-through.
		 */
		case RegionType::CHECKERBOARD_ONE:
			patterns[i].tiles.tileArray[1] = Tile(Tile::AIR);

		case RegionType::CHECKERBOARD_TWO_ALTERNATE:
			if (patterns[i].tiles.tileArray[1].getType() == Tile::NULL_TYPE)
				throw invalid_type("Tile cannot be 'NULL_TYPE' on floor");

			// If the second point is higher than, or to the left of the first
			if (patterns[i].beta.y > patterns[i].alpha.y ||
				patterns[i].beta.x < patterns[i].alpha.x)
				throw std::out_of_range(
					"Pattern is out of point range! Higher or to the left."
			);
			// For the height of the selection
			for (int j = 0; j < patterns[i].beta.y - patterns[i].alpha.y; j++)
			{
				// Draws pattern accounting for alternating rows, hence it
				// taking the current row into consideration.
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

			/*
			 * CHECKERBOARD_TWO_ROW is different from the other two
			 * CHECKERBOARDs since will generate alternating rows
			 * instead of alternating tiles.
			 */
		case RegionType::CHECKERBOARD_TWO_ROW:
			if (patterns[i].tiles.tileArray[1].getType() == Tile::NULL_TYPE)
				throw invalid_type("Tile cannot be 'NULL_TYPE' on floor");

			// If the second point is higher than, or to the left of the first
			if (patterns[i].beta.y > patterns[i].alpha.y ||
				patterns[i].beta.x < patterns[i].alpha.x)
				throw std::out_of_range(
					"Pattern is out of point range! Higher or to the left."
			);

			// For the height of the selection
			for (int j = 0; j < patterns[i].beta.y - patterns[i].alpha.y; j++)
			{
				// Draws pattern row by row, with 1 tile type per row
				// Very similar to previous checkerboard patterns.
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

		/* Connected diagonals allow for 1 extra point in the direction of
		 * where the connecting diagonal is drawn specifically at the end
		 * because a diagonal can validly be drawn with a parallel line going
		 * to its end.
		 */
		case RegionType::DIAGONAL_CONNECTED_OVER:
			{
				// Aliases for point coordinates.
				int x1 = patterns[i].alpha.x, x2 = patterns[i].beta.x,
					y1 = patterns[i].alpha.y, y2 = patterns[i].beta.y;

				// If the points are not in a valid diagonal line
				if (!(abs(y1 - y2) == abs(x1 - x2) ||
					 abs(y1 - y2) == abs(x1 - x2) - 1))
					throw std::out_of_range(
						"DIAGONAL_CONNECTED_OVER is out of point range!"
					);


				// Draws initial line
				for (int j = 0; j < abs(y1 - y2); j++)
					tiles[y1 + j][x1 + j] = patterns[i].tiles.singleTile;

				// Draws second line excluding last tile
				for (int j = 0; j < abs(y1 - y2) - 1; j++)
					tiles[y1 + j][x1 + j + 1] = patterns[i].tiles.singleTile;

				// Draws last tile if it should.
				if ((abs(y1 - y2) == abs(x1 - x2) - 1))
					tiles[y2][x2] = patterns[i].tiles.singleTile;

			}
			break;

		case RegionType::DIAGONAL_CONNECTED_UNDER:
			{
				// Aliases for point coordinates.
				int x1 = patterns[i].alpha.x, x2 = patterns[i].beta.x,
					y1 = patterns[i].alpha.y, y2 = patterns[i].beta.y;

				// If the points are not in a valid diagonal line
				if (!(abs(y1 - y2)     == abs(x1 - x2) ||
					 abs(y1 - y2) - 1 == abs(x1 - x2)))
					throw std::out_of_range(
						"DIAGONAL_CONNECTED_UNDER is out of point range!"
					);

				
				// Draws initial line
				for (int j = 0; j < abs(x1 - x2); j++)
					tiles[y1 + j][x1 + j] = patterns[i].tiles.singleTile;

				// Draws second line excluding last tile
				for (int j = 0; j < abs(x1 - x2) - 1; j++)
					tiles[y1 + j + 1][x1 + j] = patterns[i].tiles.singleTile;

				// Draws last tile if it should.
				if ((abs(y1 - y2) == abs(x1 - x2) - 1))
					tiles[y2][x2] = patterns[i].tiles.singleTile;

				break;
			}
		case RegionType::DIAGONAL_DISCONNECTED:
			{
				// Aliases for point coordinates.
				int x1 = patterns[i].alpha.x, x2 = patterns[i].beta.x,
					y1 = patterns[i].alpha.y, y2 = patterns[i].beta.y;

				// If the points are not a perfect diagonal line
				if (abs(y1 - y2) != abs(x1 - x2))
					throw std::out_of_range(
						"DIAGONAL_CONNECTED_OVER is out of point range!"
					);

				// Draws the line.
				for (int j = 0; j < abs(y1 - y2); j++)
					tiles[y1 + j][x1 + j] = patterns[i].tiles.singleTile;
			}
			break;

		case RegionType::SOLID:
			// Fills a solid box between the two points
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


void Floor::tick(double& deltatime, SentActions* actions)
{
	entityTick(deltatime, actions);
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
		
		break;

	//If the trigger condition is met, destroy tile
	case Tile::TRAP:
		
		break;

	//If the player has a key in their inventory, destroy tile
	case Tile::DOOR:
		
		break;

	default:
		break;
	}
}


// Modify to skip ticking player; handled by Game
void Floor::entityTick(double& deltatime, SentActions* actions)
{
	Player* isPlayer = nullptr;
	Enemy* isEnemy = nullptr;
	Projectile* isProjectile = nullptr;
	TileEntity* isTileEntity = nullptr;
	sf::Sprite toDraw;


	for (int i = 0; i < totalEntities; i++)
	{
		isPlayer = dynamic_cast<Player*>(entities[i]);
		isEnemy = dynamic_cast<Enemy*>(entities[i]);
		isProjectile = dynamic_cast<Projectile*>(entities[i]);
		isTileEntity = dynamic_cast<TileEntity*>(entities[i]);

		// Is Player
		if (isPlayer)
		{
			isPlayer->tick(deltatime, actions);
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
