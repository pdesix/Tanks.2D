#include "Bullet.h"

Bullet::Bullet(sf::Texture * bulletTexture, sf::Vector2f pos, Direction dir) : Sprite(bulletTexture), direction(dir)
{
	Sprite::SetPosition(pos);
	Sprite::SetRotation((dir-1)*90.f);
}

Bullet::~Bullet()
{
}

void Bullet::Move(sf::Time deltaTime)
{
	if (direction == Up)
		Sprite::Move(sf::Vector2f(0.f, -10.f));
	else if(direction == Down)
		Sprite::Move(sf::Vector2f(0.f, 10.f));
	else if(direction == Left)
		Sprite::Move(sf::Vector2f(-10.f, 0.f));
	else if (direction == Right)
		Sprite::Move(sf::Vector2f(10.f, 0.f));
}