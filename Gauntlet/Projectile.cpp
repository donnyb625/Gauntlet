#include "Projectile.h"


Projectile::Projectile(ProjectileType type, ResourceManager* resManInit,
	BoundsManager* boundManInit, double initX, double initY)
	: Entity(resManInit, boundManInit, sf::Vector2<double>(initX, initY))
{
}

Projectile::~Projectile()
{
}

void Projectile::tick(double& deltatime)
{
	switch()
}

sf::Sprite Projectile::draw()
{
	return sf::Sprite();
}