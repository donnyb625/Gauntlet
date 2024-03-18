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

		EnemyStats(int initHP, int initAD, int initSP, int initSS) :
			healthPoints(initHP), attackDamage(initAD), speed(initSP), 
			shotSpeed(initSS) {}
	};
	
	Enemy(EnemyType type, EnemyStats stats, ResourceManager* resManInit,
		BoundsManager* boundManInit);
	~Enemy();

	EnemyStats createInitStats(EnemyType type);

	void tick(double& deltatime);
	sf::Sprite draw();
private:
};