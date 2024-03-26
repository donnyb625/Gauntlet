#pragma once

#include <SFML/Graphics.hpp>
#include "BoundsManager.h"
#include "ResourceManager.h"
#include "SharedTypes.h"


// The base class for all entities, creates the contracts necessary for proper
// functionality in all derived entity types.
class Entity
{
protected:
	Entity(ResourceManager* resourceMan, BoundsManager* boundsMan,
		sf::Vector2<double> initPos)
		: resourceManager(resourceMan), boundsManager(boundsMan),
		position(initPos) {}

	virtual void tick(double deltatime) = 0;
	virtual sf::Sprite draw() = 0;
	virtual void loadSprites() = 0;
	virtual void loadSounds() = 0;

	ResourceManager* resourceManager;
	BoundsManager* boundsManager;
	sf::Vector2<double> position;
	UsableResource* sounds = nullptr;
	UsableResource* textures = nullptr;
	sf::Sprite* animationFrames = nullptr;
};