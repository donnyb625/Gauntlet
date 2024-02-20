#pragma once

#include "Entity.h"


class Enemy : public Entity
{
public:
	enum EnemyType
	{
		DEMON,
		GHOST,
		GRUNT,
		LOBBER,
		SORCERER,
		THIEF,
		DEATH
	};
	
	struct EnemyStats
	{
		int healthPoints;
		int attackDamage;
		int speed;
		int shotSpeed;
	};
	
	Enemy(EnemyType type, EnemyStats stats);
	~Enemy();

private:
	
};