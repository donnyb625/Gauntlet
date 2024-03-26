#include "Game.h"


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
	loadNextFloorData();

	while (window->isOpen())
	{
		// TotalActions is 1-indexed in practice.
		// It must be treated as such in its usages
		int totalActions = 0;
		int actionSize = 1;
		bool addedAction;
		Action * actions = new Action[actionSize]; // Max of 255 entries
		sf::Event event;
		
		while (window->pollEvent(event))
		{	
			if (event.type == sf::Event::Closed)
				window->close();
			else if (event.type == sf::Event::KeyPressed)
			{
				totalActions++;
				if (totalActions > actionSize)
					adjustActionSize(actions, actionSize, false);
				
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
				case sf::Keyboard::W:
					actions[totalActions - 1] = Action::NORTH;
					addedAction = true;
					break;
					
				case sf::Keyboard::Down:
				case sf::Keyboard::S:
					actions[totalActions - 1] = Action::SOUTH;
					addedAction = true;
					break;
					
				case sf::Keyboard::Left:
				case sf::Keyboard::A:
					actions[totalActions - 1] = Action::WEST;
					addedAction = true;
					break;
					
				case sf::Keyboard::Right:
				case sf::Keyboard::D:
					actions[totalActions - 1] = Action::EAST;
					addedAction = true;
					break;

				default:
					addedAction = false;
					break;
				}


				// Merges actions into NORTH_EAST, SOUTH_EAST, etc... format.
				if (!addedAction)
					totalActions--;
				else if (totalActions > 1)
				{
					if (actions[totalActions-2] == Action::NORTH)
					{
						if (actions[totalActions-1] == Action::EAST)
						{
							totalActions--;
							actions[totalActions-2]
								= Action::NORTH_EAST;
						}
						else if (actions[totalActions] == Action::WEST)
						{
							totalActions--;
							actions[totalActions-1]
								= Action::NORTH_WEST;
						}
					}
					else if (actions[totalActions-2] == Action::SOUTH)
					{
						if (actions[totalActions-1] == Action::EAST)
						{
							totalActions--;
							actions[totalActions-2]
								= Action::SOUTH_EAST;
						}
						else if (actions[totalActions-1] == Action::WEST)
						{
							totalActions--;
							actions[totalActions-2]
								= Action::SOUTH_WEST;
						}
					}
					else if (actions[totalActions-2] == Action::EAST)
					{
						if (actions[totalActions-1] == Action::NORTH)
						{
							totalActions--;
							actions[totalActions-2]
								= Action::NORTH_EAST;
						}
						else if (actions[totalActions-1] ==Action::SOUTH)
						{
							totalActions--;
							actions[totalActions-2]
								= Action::SOUTH_EAST;
						}
					}
					else if (actions[totalActions-2] == Action::WEST)
					{
						if (actions[totalActions-1] == Action::NORTH)
						{
							totalActions--;
							actions[totalActions-2]
								= Action::NORTH_WEST;
						}
						else if (actions[totalActions-1] ==Action::SOUTH)
						{
							totalActions--;
							actions[totalActions-2]
								= Action::SOUTH_WEST;
						}
					}
				}
			}
		}
		
		tick();
		draw();

		delete[] actions;
		actions = nullptr;
	}
}

// Helper function for adjusting the size of the actions array
Action* Game::adjustActionSize(Action* actions, int& size, bool set)
{
	int newSize = size;
	if (!set)
		newSize *= 2;
	
	Action* newActions = new Action[size*2];
	for (int i = 0; i < size; i++)
		newActions[i] = actions[i];
	size = newSize;

	delete[] actions;
	return newActions;
}

void Game::tick()
{

	floor->tick(deltatime);
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
	Entity** entities = nullptr;
	TileEntity* currentEntity = nullptr;
	TileRegion* patterns = nullptr;
	TileEntity::TileType entityType;
	Tile tiles[2];

	floorFile = std::ifstream("levelData.bin", std::ios::binary);

	if (floorFile)
	{
		FileReader reader(floorFile, true);
		FileReader::RawLevelData* data = reader.readNextLevelData();
		
		entities = new Entity*[data->totalEntities + 1]; // Player Reserve
		entities[0] = player; // first index is player
		
		for (int i = 0; i < data->totalEntities; i++)
		{
			entities[i + 1] = new TileEntity(
				data->entities[i].identification,
				&resourceManager,
				data->entities[i].x,
				data->entities[i].y,
				&boundsManager
			);
		}

		patterns = new TileRegion[data->totalPatterns];


		// Create logic for converting pattern to tile
		// initialize the bounds manager based upon patterns
		for (int i = 0; i < data->totalPatterns; i++)
		{
			for (int j = 0; j < 2; j++)
				tiles[j] = Tile(data->patterns[i].tileIDs[j]);
			
			patterns[i] = TileRegion(
				TileRegion::Point(
					data->patterns[i].positionBuffer[0],
					data->patterns[i].positionBuffer[1]
				),
				TileRegion::Point(
					data->patterns[i].positionBuffer[2],
					data->patterns[i].positionBuffer[3]
				),
				data->patterns[i].patternType,
				TileRegion::RegionTile(tiles)
			);
		}

		floor = new Floor(
			data->totalEntities,
			entities,
			data->totalEntities,
			patterns, // fails
			window,
			data->bgColor,
			data->fgColor,
			data->wallStyle,
			data->floorStyle
			);
	}
	else
		throw std::runtime_error("Could not open 'levelData.bin'!");

}