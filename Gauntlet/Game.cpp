#include "Game.h"


// Constructor for 
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
		delete entities[i];
	delete[] entities;
}

void Game::start()
{
}

void Game::tick()
{
	deltatime = timer.getElapsedTime().asMilliseconds();
	timer.restart();


	for (int i = 0; i < totalEntities; i++)
	{
		
	}
}

void Game::entityTick()
{
}

void Game::draw()
{
}
