#pragma once
#include "SharedTypes.h"
#include "Entity.h"

#ifdef GAUNTLET_UNIT_TEST_ENV
class FloorTestAccessor;
#endif

class Floor
{
public:
	Floor(int initTotalEntities, Entity** initEntities, int totalPlayers,
		int initTotalTiles, TileRegion* initTiles,
		sf::RenderWindow* initWindow, sf::Color initBG, sf::Color initFG,
		WallStyle initWallStyle, FloorStyle initFloorStyle);
	~Floor();

	void draw();
	void tick(double& deltatime, SentActions* actions);

private:
	int totalEntities, totalTiles, totalPlayers;
	Tile tiles[33][33];
	sf::RenderWindow* window = nullptr;
	Entity** entities = nullptr;
	sf::Color bgColor, fgColor;
	FloorStyle floorStyle;
	WallStyle wallStyle;


	void destroyTile(Tile::TileType type, Tile tile);
	void patternToTiles(TileRegion* patterns, int size);
	void entityTick(double& deltatime, SentActions* actions);

	
#ifdef GAUNTLET_UNIT_TEST_ENV
	friend class FloorTestAccessor;
#endif
};