#pragma once
#include "Character.h"
class Enemy : public Character
{
	int id;

public:
	Enemy(sf::Texture * texture, BulletManager * bulletMngr, MapManager * mapMngr, int ide);
	~Enemy();
	inline int GetID() { return id; }
};

