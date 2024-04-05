#pragma once
#include "SharedTypes.h"

class BoundsManager
{
public:
	BoundsManager();
	~BoundsManager();

	bool isColliding();
	void setHitbox(sf::Sprite sprite);

private:
	TileRegion** regions = nullptr;
};

