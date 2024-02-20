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

	void tick();
	sf::Sprite draw();


	Projectile(ProjectileType type);
	~Projectile();

private:
	double speed = 0;

};