#pragma once
#include "SharedTypes.h"

class BoundsManager
{
public:
	BoundsManager();
	~BoundsManager();

	bool isColliding();
	void setHitbox();

private:
	TileRegion** regions = nullptr;
};

