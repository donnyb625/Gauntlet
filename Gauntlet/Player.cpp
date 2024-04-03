#include "Player.h"


Player::Player(PlayerType type, ResourceManager* resManInit,
	BoundsManager* boundManInit, double initX, double initY)
	: Entity(resManInit, boundManInit, sf::Vector2<double>(initX, initY)),
	  stats(createInitialStats(type))
{
	// Set the stats based on the type
}

Player::~Player()
{

}


// Allows the construction of constant data in player stats.
Player::PlayerStats Player::createInitialStats(PlayerType type)
{
	switch (type)
	{
	case PlayerType::ELF:
		return PlayerStats(820, 120, 2, 2, 0, 3, 5);

	case PlayerType::VALKYRIE:
		return PlayerStats(900, 100, 5, 3, 0, 2, 3);

	case PlayerType::WARRIOR:
		return PlayerStats(980, 80, 4, 5, 0, 1, 2);

	case PlayerType::WIZARD:
		return PlayerStats(800, 100, 1, 3, 0, 5, 3);
	default:
		throw std::invalid_argument("Invalid player type");
	}
}


void Player::tick(double deltatime, SentActions* actions)
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
		stats.healthPoints += stats.healthGain; // Is this correct? Yes
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