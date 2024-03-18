#include "Game.h"


// The entrypoint for Gauntlet
int main()
{
	sf::RenderWindow window(sf::VideoMode(960, 720), "Gauntlet");
	Game gauntlet(window);

	gauntlet.start();

	return 0;
}