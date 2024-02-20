#pragma once

#include "Entity.h"


class Player : public Entity
{
public:
	enum PlayerType
	{
		WARRIOR,
		ELF,
		VALKYRIE,
		WIZARD
	};

	struct PlayerStats 
	{
		int healthPoints;
		int healthGain;
		int armor;
		int attackDamage;
		int shotSpeed;
		int magic;
		int speed;
	};

	Player(PlayerType type, PlayerStats stats);
	~Player();

	void eatFood();
	void damage();
	void attack();
	void move();

private:

};