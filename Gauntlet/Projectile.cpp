#include "Projectile.h"
#include "invalid_type.h"


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
	//(sqrt 2)/2
	const double RT2_2 = 0.70710678118654752440084436210485;

	ProjectileType type;
	Direction currentDirection;


	switch (type)
	{
	case ARROW || AXE || DAGGER || FIREBALL:
		switch (currentDirection)
		{
		case Direction::NULL_DIRECTION:
			throw invalid_type("Invalid direction");
			break;
		case Direction::NORTH:
			position.y += (deltatime / 1000);
			break;
		case Direction::SOUTH:
			position.y -= (deltatime / 1000);
			break;
		case Direction::EAST:
			position.x += (deltatime / 1000);
			break;
		case Direction::WEST:
			position.x -= (deltatime / 1000);
			break;
		case Direction::NORTH_EAST:
			position.x += RT2_2 * (deltatime / 1000);
			position.y += RT2_2 * (deltatime / 1000);
			break;
		case Direction::SOUTH_EAST:
			position.x += RT2_2 * (deltatime / 1000);
			position.y -= RT2_2 * (deltatime / 1000);
			break;
		case Direction::NORTH_WEST:
			position.x -= RT2_2 * (deltatime / 1000);
			position.y += RT2_2 * (deltatime / 1000);
			break;
		case Direction::SOUTH_WEST:
			position.x -= RT2_2 * (deltatime / 1000);
			position.y -= RT2_2 * (deltatime / 1000);
			break;
		}
	}
}

sf::Sprite Projectile::draw()
{
	return sf::Sprite();
}