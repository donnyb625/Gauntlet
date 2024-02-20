#pragma once

#include "Entity.h"


class Player : public Entity
{
public:
	void tick();
	sf::Sprite draw();
private:
};

