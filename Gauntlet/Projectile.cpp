#include "Projectile.h"


Projectile::Projectile(ProjectileType type, ResourceManager* resManInit,
	BoundsManager* boundManInit) : Entity(resManInit, boundManInit)
{
}

Projectile::~Projectile()
{
}

void Projectile::tick(double& deltatime)
{
}

sf::Sprite Projectile::draw()
{
	return sf::Sprite();
}