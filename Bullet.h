#pragma once
#include "Drawables.h"
#include "Interfaces.h"

class Bullet : public Sprite
{
	Direction direction;
public:
	Bullet(sf::Texture * bulletTexture, sf::Vector2f pos, Direction dir);
	~Bullet();
	void Move(sf::Time deltaTime);
};

