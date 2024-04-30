#include "Enemy.h"

Enemy::Enemy(EnemyType type, EnemyStats stats, ResourceManager* resManInit,
	BoundsManager* boundManInit, double initX, double initY, EnemyType initT)
	: Entity(resManInit, boundManInit, sf::Vector2<double>(initX, initY)),
		type(initT)
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


void Enemy::tick(double& deltatime, sf::Vector2<double> playerPos)
{
	//Move on the x-axis relative to player's position
	if (playerPos.x > position.x)
		position.x += stats.speed * (deltatime / 1000);
	else
		position.x -= stats.speed * (deltatime / 1000);

	//Move on the y-axis relative to player's position
	if (playerPos.y > position.y)
		position.y += stats.speed * (deltatime / 1000);
	else
		position.y -= stats.speed * (deltatime / 1000);
	
	//If touching player, deal damage


	switch (type)
	{
	case DEMON:
		//Fireball attack
		break;

	case GHOST:
		//Fade on player contact
		break;

	case GRUNT:
		//Melee
		break;

	case LOBBER:
		//Throw rock that goes over wall and predicts player movement
		break;

	case SORCERER:
		//Magic balls
		break;

	case THIEF:
		//Steals items
		break;

	case DEATH:

		break;
	}


}


sf::Sprite Enemy::draw()
{
	return sf::Sprite();
}