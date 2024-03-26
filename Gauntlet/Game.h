#pragma once

#include "ResourceManager.h"
#include "BoundsManager.h"
#include "Floor.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "FileReader.h"

class Game
{
public:
	Game(sf::RenderWindow& window);
	~Game();

	void start();

private:
	double deltatime = 0;
	int currentFloor = 0, totalFloors;
	ResourceManager resourceManager;
	BoundsManager boundsManager;
	Floor* floor = nullptr;
	Player* player = nullptr;
	sf::RenderWindow* window;
	std::ifstream floorFile;

	sf::Clock timer;


	void tick();
	void draw();
	void loadNextFloorData();
	Action* adjustActionSize(Action* actions, int &size, bool set);
};

