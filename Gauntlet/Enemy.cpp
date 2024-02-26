#include "Enemy.h"

Enemy::Enemy(EnemyType type, EnemyStats stats, ResourceManager* resManInit,
	BoundsManager* boundManInit) : Entity(resManInit, boundManInit)
{
}

Enemy::~Enemy()
{
}

void Enemy::tick()
{
}

sf::Sprite Enemy::draw()
{
	return sf::Sprite();
}
