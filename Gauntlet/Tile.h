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
		TRAP, // Is a wall that breaks on a trigger
		DOOR,
		AIR
	};

	Tile(TileType tile);
	~Tile();

	bool tick();
	void draw();
private:
};

