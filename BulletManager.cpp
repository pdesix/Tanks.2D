#include "BulletManager.h"
#include "MapManager.h"

int BulletManager::ProcessLogic(sf::Time deltaTime)
{
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		Bullet * bullet = bullets[i];
		sf::FloatRect pos(bullet->GetPosition());
		bullet->Move(deltaTime);
		if (pos.top < -30 || pos.top > 830 || pos.left < -30 || pos.left > 860)
		{
			bullets.erase(bullets.begin()+i);
			i--;
			delete bullet;
		}
		else if (CheckCollisions(bullet) == true)
		{
			bullets.erase(bullets.begin() + i);
			i--;
			delete bullet;
		}
	}
	return Codes::Null;
}

bool BulletManager::CheckCharacterCollision(sf::FloatRect playerPos)
{
	for (unsigned int i = 0; i < bullets.size(); i++)
		if (bullets[i]->GetGlobalBounds().intersects(playerPos))
		{
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
			i--;
			return true;
		}
	return false;
}

bool BulletManager::CheckCollisions(Bullet * bullet)
{
	for (unsigned int i = 0; i < mapManager->scene.size(); i++)
		if (mapManager->scene[i]->IfCollidable() && mapManager->scene[i]->GetGlobalBounds().intersects(bullet->GetGlobalBounds()))
			return true;
	return false;
}

void BulletManager::RegisterBullet(sf::Vector2f pos, Direction dir, SourceType source)
{
	if (source == SourcePlayer)
		bullets.push_back(new Bullet(playerBullet, pos, dir));
}

void BulletManager::RegisterBullet(sf::Vector2f pos, Direction dir, sf::Texture * bulletTexture)
{
	bullets.push_back(new Bullet(bulletTexture, pos, dir));
}

BulletManager::BulletManager(MapManager * mngr) : playerBullet(), mapManager(mngr), bullets(0)
{
	playerBullet = new sf::Texture();
	playerBullet->loadFromFile("sprites/playerBullet.png");
}

BulletManager::~BulletManager()
{
	for (Bullet * bullet : bullets)
		delete bullet;
	delete playerBullet;
}
