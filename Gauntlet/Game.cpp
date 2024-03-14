#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "TileEntity.h"
#include <fstream>


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
	sf::RenderWindow window(sf::VideoMode(720, 960), "Gauntlet");


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
			isPlayer->tick();
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

unsigned char Game::readData(std::ifstream& file)
{
	unsigned char result = 0;
	file.read(reinterpret_cast<char*>(&result), 1); // Reading 1 byte
	return result;
}

unsigned short Game::readSize(std::ifstream& file)
{
	unsigned char buffer[2];
	file.read(reinterpret_cast<char*>(buffer), 2); // Reading 2 bytes
	return static_cast<unsigned short>((buffer[1] << 8) | buffer[0]);
}

unsigned int Game::readColor(std::ifstream& file)
{
	unsigned char buffer[3];
	file.read(reinterpret_cast<char*>(buffer), 3); // Reading 3 bytes

	unsigned int result = buffer[0] | (buffer[1] << 8) | (buffer[2] << 16);
	return result;
}