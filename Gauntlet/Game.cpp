#include "Game.h"
#include "invalid_type.h"
#include "stdint.h"

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
					adjustActionSize(actions, actionSize, false);

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
						getKeyActionDirection(sf::Event::KeyEvent(event.key));
					break;

				case sf::Event::JoystickMoved:
					actions[totalActions - 1] = getJoystickDirection(
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
		actions = adjustActionSize(actions, actionSize, true);
		
		
		tick();
		draw();

		delete[] actions; // Used and forgotten
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

 
/* Cleans up the actions and sorts them in this priority order
 *
 * 1. Pickup
 * 2. Shooting
 * 3. Movement
 *
 * Uses bitwise operations to handle different directions
 * which also makes the code shorter and more efficient.
 */
SentActions Game::cleanActions(Action*& actions, int &size)
{
	int index = 0;
	//128 64 32 16 8 4 2 1
	// NE/NW/SE/SW/N/S/E/W
	uint8_t directionFlags = 0;
	bool shoot = false, pickup = false;
	// while they arnt all true
	// find what actions are set
	while (directionFlags != 0b11111111 && !shoot && !pickup && index < size)
	{
		try
		{
			switch (actions[index])
			{
			case Action::NORTH:
				directionFlags |= 0b00001000;
				break;

			case Action::SOUTH:
				directionFlags |= 0b00000100;
				break;

			case Action::EAST:
				directionFlags |= 0b00000010;
				break;

			case Action::WEST:
				directionFlags |= 0b00000001;
				break;

			case Action::NORTH_EAST:
				directionFlags |= 0b10000000;
				break;

			case Action::NORTH_WEST:
				directionFlags |= 0b01000000;
				break;

			case Action::SOUTH_EAST:
				directionFlags |= 0b00100000;
				break;

			case Action::SOUTH_WEST:
				directionFlags |= 0b00010000;
				break;

			case Action::SHOOT:
				shoot = true;
				break;

			case Action::PICKUP:
				pickup = true;
				break;

			default:
				throw invalid_type("Invalid action before action conversion!");
			}
		}
		catch (invalid_type& e)
		{
			std::cerr << "Error when processing actions for delivery: " << e.what();
		}
		index++;
	}
	index = 0;
	
	if (pickup)
	{
		actions[index] = Action::PICKUP;
		index++;
	}

	if (shoot)
	{
		actions[index] = Action::SHOOT;
		index++;
	}
	
	//128 64 32 16 8 4 2 1
	// NE/NW/SE/SW/N/S/E/W
	
	// Cull north/south movement if going in both directions
	if ((directionFlags & 0b00001100) == 0b00001100)
		directionFlags &= ~0b00001100;

	// Cull east/west movement if going in both directions
	if ((directionFlags & 0b00000011) == 0b00000011)
		directionFlags &= ~0b00000011;

	// Cull north_east/south_west movement if going in both directions
	if ((directionFlags & 0b10010000) == 0b10010000)
		directionFlags &= ~0b10010000;

	// Cull south_east/north_west movement if going in both directions
	if ((directionFlags & 0b01100000) == 0b01100000)
		directionFlags &= ~0b01100000;
	
	// If both north & east are set, set element to north_east
	if ((directionFlags & 0b00001010) == 0b00001010)
	{
		actions[index] = Action::NORTH_EAST;
		index++;
	}
	
	// If both north & west are set, set element to north_west
	if ((directionFlags & 0b00001001) == 0b00001001)
	{
		actions[index] = Action::NORTH_WEST;
		index++;
	}
	
	// If both south & east are set, set element to south_east
	if ((directionFlags & 0b00000110) == 0b00000110)
	{
		actions[index] = Action::SOUTH_EAST;
		index++;
	}
	
	// If both south & west are set, set element to south_west
	if ((directionFlags & 0b00000101) == 0b00000101)
	{
		actions[index] = Action::SOUTH_WEST;
	}

	// Wrap these actions in a SentActions object //

	// Create new holding array
	actions = adjustActionSize(actions, index, true);

	// Create SentActions object and return it
	return SentActions(actions, index);
}


// Gets the direction the joystick is pointed in
Action Game::getJoystickDirection(const sf::Event::JoystickMoveEvent& joystickMove)
{
	Action action = Action::NULL_ACTION;
	const double pi = 3.14159265358979323846;
	// Read the current position of the joystick's X and Y axes
	float x = sf::Joystick::getAxisPosition(joystickMove.joystickId,
		sf::Joystick::X);
	float y = sf::Joystick::getAxisPosition(joystickMove.joystickId,
		sf::Joystick::Y);

	// Dead zone handling
	float deadZone = 15.0f; // Dead zone threshold, adjust as needed

	// Calculate the angle in radians
	// Negating y because joystick y-axis is usually inverted
	float angle = std::atan2(-y, x); 

	// Convert angle to degrees
	float degrees = angle * (180.0f / pi);

	// Normalize degrees to be between 0 and 360
	if (degrees < 0)
		degrees += 360;

	// Determine the direction based on the angle
	if (degrees > 337.5 || degrees <= 22.5)
		action = Action::EAST;
	else if (degrees > 22.5 && degrees <= 67.5)
		action = Action::NORTH_EAST;
	else if (degrees > 67.5 && degrees <= 112.5)
		action = Action::NORTH;
	else if (degrees > 112.5 && degrees <= 157.5)
		action = Action::NORTH_WEST;
	else if (degrees > 157.5 && degrees <= 202.5)
		action = Action::WEST;
	else if (degrees > 202.5 && degrees <= 247.5)
		action = Action::SOUTH_WEST;
	else if (degrees > 247.5 && degrees <= 292.5)
		action = Action::SOUTH;
	else if (degrees > 292.5 && degrees <= 337.5)
		action = Action::SOUTH_EAST;

	return action; // Default case, might want to handle this differently
}

Action Game::getKeyActionDirection(const sf::Event::KeyEvent& keyPressed)
{
	Action action = Action::NULL_ACTION;

	// Handle controls
	switch (keyPressed.code)
	{
	case sf::Keyboard::Up:
	case sf::Keyboard::W:
		action = Action::NORTH;
		break;

	case sf::Keyboard::Down:
	case sf::Keyboard::S:
		action = Action::SOUTH;
		break;

	case sf::Keyboard::Left:
	case sf::Keyboard::A:
		action = Action::WEST;
		break;

	case sf::Keyboard::Right:
	case sf::Keyboard::D:
		action = Action::EAST;
		break;

	case sf::Keyboard::Space:
		action = Action::SHOOT;
		break;

	default:
		break;
	}

	return action;
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
	TileRegion* patterns = nullptr;
	Tile tiles[2];

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

}