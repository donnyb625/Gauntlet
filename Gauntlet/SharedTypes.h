#pragma once
/*
	Contains many shared enumerations / structures used throughout the program
	especially those that are used for map loading given the heavy reliance on
	pseudo-compression to lower the computational effort for collision.
*/

// The type of region pattern that it will represent;
// used for compression and ease of importing from arcade to here.
enum class RegionType
{
	SOLID,
	BOX,
	DIAGONAL_DISCONNECTED,
	DIAGONAL_CONNECTED_OVER,
	DIAGONAL_CONNECTED_UNDER,
	CHECKERBOARD_TWO_ROW, // Requires 2 tiles
	CHECKERBOARD_TWO_ALTERNATE, // Requires 2 tiles
	CHECKERBOARD_ONE
};


/* If needed, uncomment
enum class BoundType
{
	SOLID,
	BOX,
	DIAGONAL
};
*/


// The type of tile that should be referenced
enum class TileType
{
	WALL,
	WALL_BREAKABLE,
	TELEPORTER,
	TRAP,
	DOOR
};


// Used to support patterns that require multiple tiles for generation
// IE CHECKERBOARD_TWO_ROW / ALTERNATE
union RegionTile
{
	TileType Tile;
	TileType Tiles[2];
};


// A simple 2d point on a plane
struct Point
{
	double x;
	double y;
};


// A region containing tiles, this is defined for loading levels using the
// Compression we use.
struct TileRegion
{
	Point Alpha;
	Point Beta;
	RegionType Type;
	RegionTile Tiles;
};


/* If needed, uncomment
struct Bound
{
	Point Alpha;
	Point Beta;
	BoundType Type;
};
*/