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

	while (window->isOpen())
	{
		sf::Event event;

		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
	}

	tick();
	draw();
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
	RegionType* patterns = nullptr;
	TileEntity::TileType entityType;

	floorFile = std::ifstream("levelData.bin", std::ios::binary);

	if (floorFile)
	{
		FileReader reader(floorFile, true);
		FileReader::RawLevelData* data = reader.readNextLevelData();
		
		entities = new Entity * [data->totalEntities + 1]; // Player Reserve

		for (int i = 0; i < data->totalEntities; i++)
		{
			// UNFINISHED; NEEDS TO HANDLE PLAYER RESERVATION
			entities[i + 1] = new TileEntity(
				data->entities[i].identification,
				&resourceManager,
				&boundsManager
			);

		}

	}
	else
		throw std::exception::exception("Could not open 'levelData.bin'!");

}