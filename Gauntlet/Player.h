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
		int armor;
		const int attackDamage;
		const int healthGain;
		const int shotSpeed;
		const int magic;
		const int speed;

		PlayerStats(int initHP, int initHG, int initArm, int initAD,
			int initSS, int initMag, int initSpe)
			: healthPoints(initHP), armor(initArm),attackDamage(initAD), 
			healthGain(initHG), shotSpeed(initSS), magic(initMag),
		    speed(initSpe) {}
	};

	Player(PlayerType type, ResourceManager* resManInit,
		BoundsManager* boundManInit, double initX, double initY);
	~Player();

	PlayerStats createInitialStats(PlayerType type);

	sf::Sprite draw();
	void tick(double deltatime);
	void setActions(SentActions& newActions);
	void eatFood(ConsumableType consumable);
	void damage(int value);
	void attack();
	void move();

private:
	Action** actions = nullptr;
	PlayerStats stats;
};