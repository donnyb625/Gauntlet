#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "TileEntity.h"
#include <fstream>
#include <iostream>


// Starts the timer and initializes the entities.
Game::Game()
{
	timer.restart();

	entities = new Entity*[maxEntities];

	for (int i = 0; i < maxEntities; i++)
		entities[i] = nullptr;
}


// Frees the entities memory.
Game::~Game()
{
	for (int i = 0; i < maxEntities; i++)
		delete entities[i]; // Calling delete on nullptr is safe.
	delete[] entities;
}



void Game::start()
{
	// Start the game
	sf::RenderWindow window(sf::VideoMode(960, 720), "Gauntlet");


	// Presumably load the floor and entities into memory

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	tick(window);

	window.clear();
	draw(window);
}

void Game::tick(sf::RenderWindow& window)
{
	deltatime = timer.getElapsedTime().asMilliseconds();
	timer.restart();

	entityTick(window);
}

void Game::entityTick(sf::RenderWindow& window)
{
	Player* isPlayer = nullptr;
	Enemy* isEnemy = nullptr;
	Projectile* isProjectile = nullptr;
	TileEntity* isTileEntity = nullptr;
	sf::Sprite toDraw;

	for (int i = 0; i < totalEntities; i++)
	{
		isPlayer = dynamic_cast<Player*>(entities[i]);
		isEnemy = dynamic_cast<Enemy*>(entities[i]);
		isProjectile = dynamic_cast<Projectile*>(entities[i]);
		isTileEntity = dynamic_cast<TileEntity*>(entities[i]);

		// Is Player
		if (isPlayer)
		{
			isPlayer->tick(deltatime);
			toDraw = isPlayer->draw();
		}
		else if (isEnemy)
		{
			isEnemy->tick();
			toDraw = isEnemy->draw();
		}
		else if (isProjectile)
		{
			isProjectile->tick();
			toDraw = isProjectile->draw();
		}
		else if (isTileEntity)
		{
			isTileEntity->tick();
			toDraw = isTileEntity->draw();
		}

		window.draw(toDraw);
	}
}


void Game::draw(sf::RenderWindow& window)
{
	window.clear();
	window.display();
}



/*
  levelData.bin Data Structure

  File Header:   ( 1 byte : Total Levels )
  Level Header:  ( 6 byte : Color Scheme   | 1 byte      : Wall Style
         \-----> | 1 byte : floor Style    | 2 byte      : Pattern Array Size )
  Level Data:    ( 1 byte : Pattern type   | 1 or 2 byte : Tile ID )
  Entity Header: ( 2 byte : Total Entities )
  Entity Data:   ( 1 byte : Entity Type ID | 2 byte      : Position)


  The file header holds the number of levels that will actually be present in
  the file. The Level Header holds the specifics like the color schems which is
  what colors the floor and walls will use, first 3 for walls last 3 for floor.
  Then after the color scheme we have the wall and floor styles since they are
  the only two that have varying textures; and lastly we have the number of
  patterns that are contained following the header. These patterns refer to
  tile patterns specifically, and the number of tiles actually required for the
  pattern. The Level Data is an array of patterns and tile IDs so that the
  level can be constructed effectively. After we have the Level Data we will
  have the Entity Header for that specific level. this creates the following
  implicit sub-structure:

  File Header | Level Header | [ Level Data | Entity Header | Entity Data ]

  Where the array of levels also holds the specific entity data for each one as
  well. The Entity Header and Entity Data will hold the number of entities and
  respectively the ID and position of each one.
*/
void Game::loadFloorData()
{
	unsigned char byte; // Stores data enumerations
	unsigned short size; // Stores array sizes
	unsigned int color; // For color schemes

	std::ifstream file("levelData.bin", std::ios::binary);

	if (file)
	{
	}
	else
		throw std::exception::exception("Could not open 'levelData.bin'!");

}