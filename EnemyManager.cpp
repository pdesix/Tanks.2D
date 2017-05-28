#include "EnemyManager.h"
#include <iostream> // DEBUG

EnemyManager::EnemyManager(MapManager * mapMngr, BulletManager * bulletMngr, Player * playerPtr) : mapManager(mapMngr), bulletManager(bulletMngr), blueTexture(new sf::Texture()), redTexture(new sf::Texture()), greenTexture(new sf::Texture()), player(playerPtr), smokeTexture(new sf::Texture)
{
	blueTexture->loadFromFile("sprites/blueTexture.png");
	redTexture->loadFromFile("sprites/redTexture.png");
	greenTexture->loadFromFile("sprites/greenTexture.png");

	smokeTexture->loadFromFile("env/smokeGrey.png");

	bulletTextures[0] = new sf::Texture;
	bulletTextures[1] = new sf::Texture;
	bulletTextures[2] = new sf::Texture;

	bulletTextures[0]->loadFromFile("sprites/blueBullet.png");
	bulletTextures[1]->loadFromFile("sprites/redBullet.png");
	bulletTextures[2]->loadFromFile("sprites/greenBullet.png");

	sf::Texture * textures[5] = { blueTexture, redTexture, greenTexture };
	for (int i = 0; i < 5; i++)
	{
		Enemy * enemy = new Enemy(textures[i%3], bulletManager, mapManager, i%3);
		enemies.push_back(enemy);

		for (;;)
		{
			enemy->SetPosition(sf::Vector2f(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600)));
			enemy->SetDirection(static_cast<Direction>(rand() % 4));

			if (!mapManager->CheckSpawn(enemy->GetGlobalBounds()))
			{
				bool crossed = false;
				for(unsigned int j = 0; j < enemies.size()-1; j++)
					if (enemies[j]->GetGlobalBounds().intersects(enemies[i]->GetGlobalBounds()))
					{
						crossed = true;
						break;
					}
				if (!crossed) break;
			}
		}
	}
}

void EnemyManager::DeleteSmoke(Sprite * smoke)
{
	for (float i = 0.01f; i < 1.0f; i += 0.10f)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		smoke->SetScale(sf::Vector2f(i, i));
	}

	for (unsigned int i = 0; i < smokes.size(); i++)
		if (smokes[i] == smoke)
			smokes.erase(smokes.begin() + i);
	delete smoke;

	deletors.erase(deletors.begin());
}

EnemyManager::~EnemyManager()
{
	for (Enemy * enemy : enemies)
		delete enemy;
	delete redTexture;
	delete greenTexture;
	delete blueTexture;
	for (sf::Texture * texture : bulletTextures)
		delete texture;
}

void EnemyManager::MovePlayer()
{
	if (player->Move())
		for (unsigned int i = 0; i < enemies.size(); i++)
			if (enemies[i]->GetGlobalBounds().intersects(player->GetGlobalBounds()))
			{
				player->Move(-1);
				return;
			}
}

void EnemyManager::MakeDecision(Enemy * enemy)
{
}

int EnemyManager::ProcessLogic(sf::Time deltaTime)
{
	bulletManager->ProcessLogic(deltaTime);
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		Enemy *& enemy = enemies[i];
		if (enemy->GetID() == 0 || enemy->GetID() == 2 || enemy->GetID() == 1)// Blue, Red, Green
		{
			for (;;)
			{
				if (!enemy->Move(1))
				{
					enemy->SetDirection(static_cast<Direction>(rand() % 4));
				}
				else
				{
					for (unsigned int j = 0; j < enemies.size(); j++)
					{
						if (enemy->GetGlobalBounds().intersects(enemies[j]->GetGlobalBounds()) && enemies[j]->GetID() != enemy->GetID())
						{
							enemy->Move(-1);
						}
					}
					break;
					if (enemy->GetGlobalBounds().intersects(player->GetGlobalBounds()))
					{
						enemy->Move(-1);
						break;
					}
					if (rand() % 100 < 1)
					{
						enemy->Shoot(bulletTextures[enemy->GetID()]);
					}
				}
			}
		}
		if (enemy->GetID() == 1 || enemy->GetID() == 2)
		{
			Direction toShoot = static_cast<Direction>(EnemyLogic::GetDirection(enemy->GetGlobalBounds(), player->GetGlobalBounds()));
			if (toShoot == Wrong)
			{
				for (unsigned int x = 0; x < enemies.size(); x++)
				{
					if (enemies[x]->GetID() == enemy->GetID())
						continue;
					if (toShoot != Wrong)
					{
						enemy->SetDirection(toShoot);
						if (enemy->Move())
							enemy->Shoot(bulletTextures[enemy->GetID()]);
						break;
					}
				}
			}
			if (toShoot != Wrong)
			{
				enemy->SetDirection(toShoot);
			}
		}

		if (bulletManager->CheckCharacterCollision(enemies[i]->GetGlobalBounds()))
		{
			smokes.push_back(new Sprite(smokeTexture));
			smokes[smokes.size() - 1]->SetPosition(sf::Vector2f(enemies[i]->GetPosition().left, enemies[i]->GetPosition().top));
			smokes[smokes.size() - 1]->SetScale(sf::Vector2f(0.1f, 0.1f));
			deletors.push_back(new std::thread(&EnemyManager::DeleteSmoke, this, smokes[smokes.size() - 1]));
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
			i--;
			if (enemies.size() == 0)
				return Codes::GameWin;
			break;
		}
	}

	if (bulletManager->CheckCharacterCollision(player->GetGlobalBounds()))
	{
		smokes.push_back(new Sprite(smokeTexture));
		smokes[smokes.size() - 1]->SetPosition(sf::Vector2f(player->GetPosition().left, player->GetPosition().top));
		smokes[smokes.size() - 1]->SetScale(sf::Vector2f(0.1f, 0.1f));
		deletors.push_back(new std::thread(&EnemyManager::DeleteSmoke, this, smokes[smokes.size() - 1]));
		return Codes::GameLose;
	}
	return Codes::Null;
}