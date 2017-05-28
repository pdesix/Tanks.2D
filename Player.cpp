#include "Player.h"

void Player::Shoot()
{
	if (!canShoot) return;
	shooted = true;
	sf::Vector2f pos(Sprite::GetPosition().left, Sprite::GetPosition().top);
	switch (direction)
	{
	case Up:
		pos.x += (Sprite::sprite->getGlobalBounds().width - BulletManager::GetBulletWidth()) / 2;
		pos.y -= BulletManager::GetBulletHeight() + 4;
		break;
	case Down:
		pos.x += (Sprite::sprite->getGlobalBounds().width) / 2 + BulletManager::GetBulletWidth() / 2;
		pos.y += Sprite::sprite->getGlobalBounds().height + BulletManager::GetBulletHeight() + 2;
		break;
	case Right:
		pos.x += Sprite::sprite->getGlobalBounds().height + BulletManager::GetBulletHeight() + 9;
		pos.y += (Sprite::sprite->getGlobalBounds().width) / 2 - BulletManager::GetBulletWidth() / 2 - 3;
		break;
	case Left:
		pos.x -= BulletManager::GetBulletHeight() + 4;
		pos.y += (Sprite::sprite->getGlobalBounds().height) / 2 + BulletManager::GetBulletWidth() / 2;
		break;
	}
	Character::bulletManager->RegisterBullet(pos, direction, BulletManager::SourcePlayer);
	canShoot = false;
	reset = new std::thread(&Character::ResetShooting, this);
	reset->detach();
}

Player::Player(sf::Texture * playerTexture, BulletManager * mngr, MapManager * mapMngr) : Character(playerTexture, mngr, mapMngr)
{
}

Player::~Player()
{
}