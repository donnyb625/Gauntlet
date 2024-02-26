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
		BoundsManager* boundManInit);
	~Projectile();

	void tick();
	sf::Sprite draw();

private:
	double speed = 0;

};