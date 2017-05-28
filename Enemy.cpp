#include "Enemy.h"

Enemy::Enemy(sf::Texture * texture, BulletManager * bulletMngr, MapManager * mapMngr, int ide) : Character(texture, bulletMngr, mapMngr), id(ide)
{
	reset = nullptr;
}

Enemy::~Enemy()
{
}