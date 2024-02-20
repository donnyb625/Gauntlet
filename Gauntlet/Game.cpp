#include "Game.h"


Game::Game()
{
	//resourceManager.l
	timer.restart();
}

Game::~Game()
{
}

void Game::start()
{
}

void Game::tick()
{


	deltatime = timer.getElapsedTime().asMilliseconds();
	timer.restart();
}

void Game::entityTick()
{
}

void Game::draw()
{
}
