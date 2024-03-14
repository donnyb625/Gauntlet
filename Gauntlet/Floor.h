#pragma once
#include "SharedTypes.h"

class Floor
{
public:
	Floor();
	~Floor();

	void draw();
	void tick();
	void setWindow(sf::RenderWindow& window);

private:
	Tile* tiles;
	sf::RenderWindow* window = nullptr;

	void destroyTile(Tile::TileType type, Tile tile);
};