#include "Game.h"
#include "FileReader.h"
#include <iostream>
#include "GameLib.h"

// Starts the timer.
Game::Game(sf::RenderWindow& initWindow) : window(&initWindow)
{
	timer.restart();

	return;
}


// Frees the entities memory.
Game::~Game()
{
	delete floor;
}


void Game::start()
{
	// Presumably load the floor and entities into memory
	try
	{
		loadNextFloorData();
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what();
		std::terminate();
	}
	catch (std::exception& e)
	{
		std::cerr << "Undefined exception: " << e.what();
		std::terminate();
	}

	while (window->isOpen())
	{
		// TotalActions is 1-indexed in practice.
		// It must be treated as such in its usages
		int totalActions = 0;
		int actionSize = 1;
		Action * actions = new Action[actionSize]; // Max of 255 entries
		sf::Event event;
		
		for (int i = 0; i < actionSize; i++)
			actions[i] = Action::NULL_ACTION;

		while (window->pollEvent(event))
		{	
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;

				// Handle keyboard based actions
			case sf::Event::KeyPressed:
			case sf::Event::JoystickMoved:
			case sf::Event::JoystickButtonPressed:
				totalActions++;
				if (totalActions > actionSize)
					GameLib::adjustActionSize(actions, actionSize, false);

				// Dummy exception for unit tests
				try
				{
					if (totalActions > actionSize || totalActions < 1)
						throw std::out_of_range
						("Action parsing - out of bounds");
				}
				catch (std::out_of_range& e)
				{
					std::cerr << e.what();
				}

				// Get the action in different ways
				switch (event.type)
				{
				case sf::Event::KeyPressed:
					actions[totalActions - 1] =
						GameLib::getKeyActionDirection(sf::Event::KeyEvent(event.key));
					break;

				case sf::Event::JoystickMoved:
					actions[totalActions - 1] = GameLib::getJoystickDirection(
						sf::Event::JoystickMoveEvent(event.joystickMove));
					break;

				case sf::Event::JoystickButtonPressed:
					if (event.joystickButton.button == 1)
						actions[totalActions - 1] = Action::SHOOT;
					break;

				default:
					break;
				}

				// If action is null then ignore
				if (actions[totalActions - 1] == Action::NULL_ACTION)
					totalActions--;

				break;

			default:
				// Ignore event
				break;
			}
		}

		actionSize = totalActions;
		actions = GameLib::adjustActionSize(actions, actionSize, true);
		
		
		tick(GameLib::cleanActions(actions, actionSize));
		draw();

		delete[] actions; // Used and forgotten
		actions = nullptr;
	}
}

void Game::tick(SentActions actions)
{
	floor->tick(deltatime, &actions);
}

void Game::draw()
{
	window->clear();
	window->display();
	deltatime = timer.getElapsedTime().asMilliseconds();
	timer.restart();
}



void Game::loadNextFloorData()
{
	const int SIZE = 32;
	Entity** entities = nullptr;
	TileRegion* patterns = nullptr;
	Tile tiles[2];
	char testFloor[SIZE][SIZE] =
	{
		{'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'x', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', 'w', 'w', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w', },
		{'w', 'x', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'x', 'w', },
		{'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', },
	};



	/*
	floorFile = std::ifstream("levelData.bin", std::ios::binary);

	if (floorFile)
	{
		FileReader reader(floorFile, true);
		FileReader::RawLevelData data = reader.readNextLevelData();
		
		entities = new Entity*[data.totalEntities + 1]; // Player Reserve
		entities[0] = player; // first index is player
		
		for (int i = 0; i < data.totalEntities; i++)
		{
			entities[i + 1] = new TileEntity(
				data.entities[i].identification,
				&resourceManager,
				data.entities[i].x,
				data.entities[i].y,
				&boundsManager
			);
		}

		patterns = new TileRegion[data.totalPatterns];


		// Create logic for converting pattern to tile
		// initialize the bounds manager based upon patterns
		for (int i = 0; i < data.totalPatterns; i++)
		{
			for (int j = 0; j < 2; j++)
				tiles[j] = Tile(data.patterns[i].tileIDs[j]);
			
			patterns[i] = TileRegion(
				TileRegion::Point(
					data.patterns[i].positionBuffer[0],
					data.patterns[i].positionBuffer[1]
				),
				TileRegion::Point(
					data.patterns[i].positionBuffer[2],
					data.patterns[i].positionBuffer[3]
				),
				data.patterns[i].patternType,
				TileRegion::RegionTile(tiles)
			);
		}

		floor = new Floor(
			data.totalEntities,
			entities,
			1, // Only one player -- Testing
			data.totalEntities,
			patterns,
			window,
			data.bgColor,
			data.fgColor,
			data.wallStyle,
			data.floorStyle
		);
	}
	else
		throw std::runtime_error("Could not open 'levelData.bin'!");
	*/

	for (int x = 0; x < SIZE; x++)
	{
		for (int y = 0; y < SIZE; y++)
		{
			switch (testFloor[x][y])
			{
			case 'w':


			}
		}
	}
}