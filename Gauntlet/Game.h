#pragma once

#include "ResourceManager.h"
#include "BoundsManager.h"
#include "Floor.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();

	void start();

private:
	double deltatime = 0;
	int totalEntities = 0, maxEntities = 32;
	ResourceManager resourceManager;
	BoundsManager boundsManager;
	Floor floor;
	Entity** entities;

	sf::Clock timer;

	void tick(sf::RenderWindow& window);
	void entityTick(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void loadFloorData();
};

