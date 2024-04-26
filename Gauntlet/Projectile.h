#pragma once

#include "Entity.h"


class Projectile : public Entity
{
public:
	enum ProjectileType
	{
		ARROW,
		SPELL_BALL_WIZARD,
		SPELL_BALL_SORCERER,
		FIREBALL,
		ROCK,
		DAGGER,
		AXE
	};

	Projectile(ProjectileType type, ResourceManager* resManInit,
		BoundsManager* boundManInit, double initX, double initY, Direction direction);
	~Projectile();

	void tick(double& deltatime, Direction);
	sf::Sprite draw();

private:
	double speed = 0;

};