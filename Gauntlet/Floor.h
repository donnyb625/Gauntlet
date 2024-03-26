#pragma once
#include "SharedTypes.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "TileEntity.h"

class Floor
{
public:
	Floor(int initTotalEntities, Entity** initEntities,
		int initTotalTiles, Tile* initTiles,
		sf::RenderWindow* initWindow, sf::Color initBG, sf::Color initFG,
		WallStyle initWallStyle, FloorStyle initFloorStyle);
	~Floor();

	void draw();
	void tick(double& deltatime);

private:
	int totalEntities, totalTiles;
	Tile* tiles = nullptr;
	sf::RenderWindow* window = nullptr;
	Entity** entities = nullptr;
	sf::Color bgColor, fgColor;
	FloorStyle floorStyle;
	WallStyle wallStyle;


	void destroyTile(Tile::TileType type, Tile tile);
	void entityTick(double& deltatime);
};