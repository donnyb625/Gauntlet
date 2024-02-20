#pragma once

#include "Entity.h"


class TileEntity : public Entity
{
public:
	void tick();
	sf::Sprite draw();
private:
};

