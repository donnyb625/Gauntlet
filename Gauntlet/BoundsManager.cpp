#include "BoundsManager.h"


BoundsManager::BoundsManager()
{

}


BoundsManager::~BoundsManager()
{

}


bool BoundsManager::isColliding()
{
	bool colliding = false;

	return colliding;
}


void BoundsManager::setHitbox(sf::Sprite sprite)
{
	sf::FloatRect hitbox = sprite.getGlobalBounds();
}