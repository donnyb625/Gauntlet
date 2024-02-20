#pragma once

#include "Entity.h"


class Enemy : public Entity
{
public:
	void tick();
	sf::Sprite draw();
private:
};