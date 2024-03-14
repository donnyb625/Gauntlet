#include "Enemy.h"

Enemy::Enemy(EnemyType type, EnemyStats stats, ResourceManager* resManInit,
	BoundsManager* boundManInit) : Entity(resManInit, boundManInit)
{

}

Enemy::~Enemy()
{
}


//Create the initial stats for enemies
Enemy::EnemyStats Enemy::createInitStats(EnemyType type)
{
	switch (type)
	{
	case DEMON:
		return { 0, 0, 0, 0 };
	case GHOST:
		return { 0, 0, 0, 0 };
	case GRUNT:
		return { 0, 0, 0, 0 };
	case LOBBER:
		return { 0, 0, 0, 0 };
	case SORCERER:
		return { 0, 0, 0, 0, };
	case THIEF:
		return { 0, 0, 0, 0, };
	case DEATH:
		return { 0, 0, 0, 0 };
	default:
		throw std::invalid_argument("Invalid enemy type");
	}
}


void Enemy::tick()
{
}

sf::Sprite Enemy::draw()
{
	return sf::Sprite();
}
