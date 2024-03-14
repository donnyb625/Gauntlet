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
	};

	Player(PlayerType type, ResourceManager* resManInit,
		BoundsManager* boundManInit);
	~Player();

	void tick(double deltatime);
	void setActions(SentActions& newActions);

	sf::Sprite draw();

	void eatFood(ConsumableType consumable);
	void damage(int value);
	void attack();
	void move();

private:
	Action** actions = nullptr;
	PlayerStats stats;
};