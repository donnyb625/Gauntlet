#pragma once

#include "Entity.h"
#include "Animatable.h"

class Enemy : public Entity, private Animatable
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
		BoundsManager* boundManInit, double initX, double initY,
		EnemyType initT);
	~Enemy();

	EnemyStats createInitStats(EnemyType type);
	EnemyType type;

	void tick(double& deltatime);
	sf::Sprite draw();
private:
};