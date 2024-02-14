#pragma once

#include "ResourceManager.h"
#include "BoundsManager.h"
#include "Floor.h"

class Game
{
public:
private:
	double deltatime = 0;
	ResourceManager resourceManager;
	BoundsManager boundsManager;
	Floor floor;

};

