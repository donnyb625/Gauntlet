#include "Projectile.h"


Projectile::Projectile(ProjectileType type, ResourceManager* resManInit,
	BoundsManager* boundManInit, double initX, double initY, Direction direction)
	: Entity(resManInit, boundManInit, sf::Vector2<double>(initX, initY))
{
}

Projectile::~Projectile()
{
}

void Projectile::tick(double& deltatime, Direction)
{
	ProjectileType type;
	Direction currentDirection;

	//Store which direction the character is facing
	switch (type)
	{
	case ARROW || AXE || DAGGER || FIREBALL:
		
	}
}

sf::Sprite Projectile::draw()
{
	return sf::Sprite();
}