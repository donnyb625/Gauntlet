#pragma once
#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


/*
	Contains many shared enumerations / structures used throughout the program,
	especially those that are used for map loading given the heavy reliance on
	pseudo-compression to lower the computational effort for collision.
*/

// Used when reading and encoding files
typedef unsigned char byte;
typedef unsigned short size;
typedef unsigned int color;

// The type of region pattern that it will represent;
// used for compression and ease of importing from arcade to here.
enum class RegionType
{
	NULL_TYPE,
	SOLID,
	BOX,
	DIAGONAL_DISCONNECTED,
	DIAGONAL_CONNECTED_OVER,
	DIAGONAL_CONNECTED_UNDER,
	CHECKERBOARD_TWO_ROW, // Requires 2 tiles
	CHECKERBOARD_TWO_ALTERNATE, // Requires 2 tiles
	CHECKERBOARD_ONE
};


// List of resource categories that can be requested by a resource holder
enum class ResourceType
{
	NULL_TYPE,
	MOVE,
	ATTACK,
	SPAWN,
	BREAK,
	AMBIENT,
	GENERIC
};


// List of resource holders, IE things that can request their resources
// This is subject to change.
enum class ResourceIdentifier
{
	DEMON_SPAWNER,
	GHOST_SPAWNER,
	GRUNT_SPAWNER,
	LOBBER_SPAWNER,
	SORCERER_SPAWNER,
	THIEF_SPAWNER,
	DEMON,
	GHOST,
	GRUNT,
	LOBBER,
	SORCERER,
	THIEF,
	KEY,
	BOMB_POTION,
	INVISIBILITY_POTION,
	EXTRA_POWER_POTION,
	MEAT_1,
	MEAT_2,
	BOOZE,
	POISON
};


// All of the consumable items
enum class ConsumableType
{
	BOMB_POTION,
	INVISIBILITY_POTION,
	EXTRA_POWER_POTION,
	MEAT_1,
	MEAT_2,
	BOOZE,
	POISON
};


// All the possible wall styles
enum class WallStyle
{
	NULL_STYLE,
	EXAMPLE_1
};


// All the possible wall styles
enum class FloorStyle
{
	NULL_STYLE,
	EXAMPLE_1
};


// A resource that is used by various classes for textures and sounds
struct UsableResource
{
	// This stores either a sound or a texture
	union Resource
	{
		sf::SoundBuffer const * sound;
		sf::Texture const * texture;

		Resource(sf::SoundBuffer const * const s) : sound(s) {}
		Resource(sf::Texture const * const t) : texture(t) {}

		~Resource() = default;
	};

	// It cannot modify any of the data not point anywhere else
	// only access what it was given
	Resource const * const resource;
	const int count; // Number of animation frames / sounds
	const ResourceType type;

	UsableResource(Resource* initResource, int initCount,
		ResourceType initType)
		: resource(initResource), count(initCount), type(initType) {}
};


// A region containing tiles, this is defined for loading levels using the
// Compression we use.
struct TileRegion
{
	TileRegion& operator=(const TileRegion& other)
	{
		if (this != &other)
		{
			alpha = other.alpha;
			beta = other.beta;
			type = other.type;
			tiles = other.tiles;
		}
		return *this;
	}

	// A simple 2d point on a plane
	struct Point
	{
		unsigned char x;
		unsigned char y;

		Point(unsigned char initX, unsigned char initY)
			: x(initX), y(initY) {}

		Point() : x(0), y(0) {}
	};

	// Used to support patterns that require multiple tiles for generation
	// IE CHECKERBOARD_TWO_ROW / ALTERNATE
	// See Floor::patternToTiles() for more information.
	union RegionTile
	{
		Tile singleTile;
		Tile tileArray[2];

		RegionTile(Tile tile) : singleTile(tile) {}
		RegionTile(Tile tile[2])
		{
			tileArray[0] = tile[0];
			tileArray[1] = tile[1];
		}
		RegionTile() : singleTile(Tile(Tile::TileType::NULL_TYPE)) {}

		~RegionTile() = default;
	};

	Point alpha;
	Point beta;
	RegionType type;
	RegionTile tiles;

	TileRegion(Point upperLeft, Point lowerRight,
		RegionType pattern, RegionTile patternTile)
		: alpha(upperLeft), beta(lowerRight), type(pattern), tiles(patternTile)
		{}

	TileRegion() : type(RegionType::NULL_TYPE) {}
};


// All of the possible actions that can be sent
enum class Action
{
	NULL_ACTION,
	NORTH,
	SOUTH,
	EAST,
	WEST,
	NORTH_EAST,
	SOUTH_EAST,
	NORTH_WEST,
	SOUTH_WEST,
	SHOOT,
	PICKUP, // Will require further implementation, generic for now
	MAGIC //Use stored bomb potion
};


// Used for sending actions to the player when ticking
struct SentActions
{
	Action const * const actions;
	const int SIZE;

	SentActions(Action* initActions, int initSize)
		: actions(initActions), SIZE(initSize) {}
};