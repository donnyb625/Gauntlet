#pragma once


// Represents a Tile placed on a floor.
class Tile
{
public:
	// The type of tile that should be referenced
	enum TileType
	{
		WALL,
		WALL_BREAKABLE,
		TELEPORTER,
		TRAP, // Is a wall
		DOOR
	};

	Tile(TileType tile);

	bool tick();
private:
};

