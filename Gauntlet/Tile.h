#pragma once


// Represents a Tile placed on a floor.
class Tile
{
public:
	// The type of tile that should be referenced
	enum TileType
	{
		NULL_TYPE, // default
		WALL,
		WALL_BREAKABLE,
		TELEPORTER,
		TRAP, // Is a wall that breaks on a trigger
		DOOR,
		AIR
	};

	Tile(TileType tile);
	Tile() : type(NULL_TYPE) {}
	~Tile() = default;
	
	bool tick();
	void draw();
	TileType getType();
private:

	TileType type;
};

