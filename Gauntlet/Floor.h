#pragma once
#include "SharedTypes.h"
#include "Game.h"

class Floor
{
public:
	Floor(sf::RenderWindow& window);
	~Floor();

	void draw(sf::RenderWindow& window);
	void tick();

private:
	Tile* tiles;

	void destroyTile(Tile::TileType type, Tile tile);
};