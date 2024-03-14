#include "Player.h"


Player::Player(PlayerType type, ResourceManager* resManInit,
	BoundsManager* boundManInit) : Entity(resManInit, boundManInit)
{

	// Set the stats based on the type
	switch (type)
	{
	case PlayerType::ELF:
		break;

	case PlayerType::VALKYRIE:
		break;

	case PlayerType::WARRIOR:
		break;

	case PlayerType::WIZARD:
		break;

	}
}

Player::~Player()
{

}


void Player::tick(double deltatime)
{
}

void Player::setActions(SentActions& newActions)
{


}

sf::Sprite Player::draw()
{
	return sf::Sprite();
}


void Player::eatFood(ConsumableType consumable)
{
	switch (consumable)
	{
	case ConsumableType::MEAT_1:
	case ConsumableType::MEAT_2:
	case ConsumableType::BOOZE:
		stats.healthPoints += stats.healthGain; // Is this correct?
		break;

	case ConsumableType::POISON:
		damage(5); // Insert an accurate value here
		break;

	default:
		throw std::invalid_argument("Non-food consumable provided!");
	}

	return;
}


void Player::damage(int value)
{
	stats.healthPoints -= value;

	return;
}


void Player::attack()
{

}


void Player::move()
{

}