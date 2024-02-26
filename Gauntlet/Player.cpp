#include "Player.h"


Player::Player(PlayerType type, PlayerStats stats, ResourceManager* resManInit,
	BoundsManager* boundManInit) : Entity(resManInit, boundManInit)
{

}

Player::~Player()
{

}


void Player::tick()
{
}

sf::Sprite Player::draw()
{
	return sf::Sprite();
}


void Player::eatFood()
{

}


void Player::damage()
{

}


void Player::attack()
{

}


void Player::move()
{

}