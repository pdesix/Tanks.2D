#pragma once
#include <thread>
#include "Drawables.h"
#include "Interfaces.h"
#include "BulletManager.h"

class Character : public Sprite
{
public:
	bool shooted;
	bool Move(int reverse = 1);
	void Shoot(sf::Texture * bulletTexture);
	void SetDirection(Direction dir);
	void ResetShooting();
	Direction GetDirection() { return direction; }
	std::thread * reset;

	Character(sf::Texture * texture, BulletManager * bulletMngr, MapManager * mapMngr);
	virtual ~Character();

protected:
	bool canShoot;
	BulletManager * bulletManager;
	MapManager * mapManager;
	Direction direction;
};