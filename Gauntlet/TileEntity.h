#pragma once

#include "Entity.h"


// Is an entity that serves the same basic purpose of a entity, just with
// tile based characteristics.
class TileEntity : public Entity
{
public:
	enum TileType
	{
		NULL_TYPE,
		DEMON_S,
		GHOST_S,
		GRUNT_S,
		LOBBER_S,
		SORCERER_S,
		THIEF_S,
		KEY,
		BOMB_POTION,
		INVISIBILITY_POTION,
		EXTRA_POWER_POTION,
		MEAT_1,
		MEAT_2,
		BOOZE,
		POISON
	};
	
	TileEntity(TileType type, ResourceManager* resManInit,
		int x, int y, BoundsManager* boundManInit);
	~TileEntity();

	void tick(double deltatime);
	sf::Sprite draw();

	void isPoison(TileType type);

private:
	// Needs to be implemented. implementation requires resource manager.
	void loadSprites();
	void loadSounds();

	TileType type;
};

