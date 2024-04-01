#pragma once

#include "ResourceManager.h"
#include "BoundsManager.h"
#include "Floor.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <fstream>

// Forward declaration for private data accessor in test environment.
#ifdef GAUNTLET_UNIT_TEST_ENV
class GameTestAccessor;
#endif

class Game
{
public:
	Game(sf::RenderWindow& window);
	~Game();

	void start();

private:
	double deltatime = 0;
	ResourceManager resourceManager;
	BoundsManager boundsManager;
	Floor* floor = nullptr;
	Player* player = nullptr;
	sf::RenderWindow* window;
	std::ifstream floorFile;

	sf::Clock timer;


	void tick(SentActions actions);
	void draw();
	void loadNextFloorData();

	// Only declare as a friend IF in a testing environment.
#ifdef GAUNTLET_UNIT_TEST_ENV
	friend class GameTestAccessor;
#endif
};

