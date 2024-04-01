#include "GameLib.h"
#include "invalid_type.h"
#include <cstdint>
#include <iostream>


namespace GameLib
{
	// Helper function for adjusting the size of the actions array
	Action* adjustActionSize(Action* actions, int& size, bool set)
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
SentActions cleanActions(Action*& actions, int &size)
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
Action getJoystickDirection(const sf::Event::JoystickMoveEvent& joystickMove)
{
	Action action = Action::NULL_ACTION;
	const double pi = 3.14159265358979323846;
	// Read the current position of the joystick's X and Y axes
	double x = sf::Joystick::getAxisPosition(joystickMove.joystickId,
		sf::Joystick::X);
	double y = sf::Joystick::getAxisPosition(joystickMove.joystickId,
		sf::Joystick::Y);

	// Dead zone handling
	double deadZone = 15.0f; // Dead zone threshold, adjust as needed

	// Calculate the angle in radians
	// Negating y because joystick y-axis is usually inverted
	double angle = std::atan2(-y, x); 

	// Convert angle to degrees
	double degrees = angle * (180.0f / pi);

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
	
	Action getKeyActionDirection(const sf::Event::KeyEvent& keyPressed)
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
			
		case sf::Keyboard::L:
		case sf::Keyboard::Space:
			action = Action::SHOOT;
			break;

		default:
			break;
		}

		return action;
	}
}