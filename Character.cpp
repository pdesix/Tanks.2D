#include "Character.h"

void Character::Shoot(sf::Texture * bulletTexture)
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
	Character::bulletManager->RegisterBullet(pos, direction, bulletTexture);
	canShoot = false;
	reset = new std::thread(&Character::ResetShooting,this);
}

bool Character::Move(int reverse)
{
	sf::Vector2f location(0, 0);
	sf::FloatRect newPos(Sprite::GetGlobalBounds());
	if (direction == 0)
	{
		location.x -= 5.f * reverse;
		newPos.left -= 5.f * reverse;
	}
	else if (direction == 2)
	{
		location.x += 5.f * reverse;
		newPos.left += 5.f * reverse;
	}
	else if (direction == 3)
	{
		location.y += 5.f * reverse;
		newPos.top += 5.f * reverse;
	}
	else if (direction == 1)
	{
		location.y -= 5.f * reverse;
		newPos.top -= 5.f * reverse;
	}
	if (!mapManager->CheckCollisions(newPos))
	{
		Sprite::Move(location);
		return true;
	}
	return false;
}

void Character::SetDirection(Direction dir) 
{
	if (dir == direction) return;
	if (dir == Down)
	{
		if(direction == Right)
			Sprite::Move(sf::Vector2f(0, -sprite->getGlobalBounds().width));
		else if(direction == Left)
			Sprite::Move(sf::Vector2f(-sprite->getGlobalBounds().height, 0));
		else if(direction == Up)
			Sprite::Move(sf::Vector2f(-sprite->getGlobalBounds().height + 4, -sprite->getGlobalBounds().width));
	}
	else if (dir == Up)
	{
		if (direction == Right)
			Sprite::Move(sf::Vector2f(sprite->getGlobalBounds().height, 0));
		else if (direction == Left)
			Sprite::Move(sf::Vector2f(0, sprite->getGlobalBounds().width));
		else if (direction == Down)
			Sprite::Move(sf::Vector2f(sprite->getGlobalBounds().height-4, sprite->getGlobalBounds().width));
	}
	else if (dir == Right)
	{
		if (direction == Left)
			Sprite::Move(sf::Vector2f(-sprite->getGlobalBounds().height, sprite->getGlobalBounds().width-2));
		else if(direction == Up)
			Sprite::Move(-sf::Vector2f(sprite->getGlobalBounds().height, 0));
		else if (direction == Down)
			Sprite::Move(sf::Vector2f(0, sprite->getGlobalBounds().height));
	}
	else if (dir == Left)
	{
		if (direction == Right)
			Sprite::Move(sf::Vector2f(sprite->getGlobalBounds().height, -sprite->getGlobalBounds().width+3));
		else if (direction == Up)
			Sprite::Move(sf::Vector2f(0, -sprite->getGlobalBounds().height));
		else if (direction == Down)
			Sprite::Move(sf::Vector2f(sprite->getGlobalBounds().height, 0));
	}
	Sprite::SetRotation(90.f + (dir * 90.f)); 
	direction = dir;
}

void Character::ResetShooting() 
{ 
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	canShoot = true; 
}

Character::Character(sf::Texture * texture, BulletManager * bulletMngr, MapManager * mapMngr) : Sprite(texture), 
	bulletManager(bulletMngr), mapManager(mapMngr), canShoot(true), direction(Up), shooted(false)
{
	Sprite::SetRotation(180);
	Sprite::SetScale(sf::Vector2f(0.5, 0.5));
}


Character::~Character()
{
	if (shooted)
	{
		reset->join();
		delete reset;
		reset = nullptr;
	}
}