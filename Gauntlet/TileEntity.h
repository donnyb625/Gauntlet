#pragma once

#include "Entity.h"


class TileEntity : public Entity
{
public:
	enum TileType
	{
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
	
	TileEntity(TileType type);
	~TileEntity();

	void isPoison(TileType type);
	void method(TileType type);

private:
};