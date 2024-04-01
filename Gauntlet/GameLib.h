#pragma once
#include "SharedTypes.h"
#include <SFML/Window.hpp>

namespace GameLib {
	Action* adjustActionSize(Action* actions, int &size, bool set);
    Action getJoystickDirection(
        const sf::Event::JoystickMoveEvent& joystickMove);
	Action getKeyActionDirection(const sf::Event::KeyEvent& keyPressed);
    SentActions cleanActions(Action*& actions, int &size);
}