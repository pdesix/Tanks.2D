#pragma once
#include "Character.h"
class Player : public Character
{
public:
	Player(sf::Texture * playerTexture, BulletManager * mngr, MapManager * mapMngr);
	~Player();
	void Shoot();
};