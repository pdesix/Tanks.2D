#include "GameState.h"

GameState::GameState(sf::RenderWindow * rWindow) : mapManager(new MapManager()), playerTexture(new sf::Texture()), bulletManager(), enemyManager(), renderWindow(rWindow)
{
	bulletManager = new BulletManager(mapManager);
	mapManager->GenerateMap(renderWindow);
	playerTexture->loadFromFile("sprites/playerTexture.png");
	
	player = new Player(playerTexture, bulletManager, mapManager);
	for (;;)
	{
		player->SetPosition(sf::Vector2f(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600)));
		player->SetDirection(static_cast<Direction>(rand() % 4));
		if (!mapManager->CheckSpawn(player->GetGlobalBounds()))
			break;
	}

	enemyManager = new EnemyManager(mapManager, bulletManager, player);
}

int GameState::ProcessLogic(sf::Time deltaTime) 
{
	return enemyManager->ProcessLogic(deltaTime);
}

int GameState::ManageGraphic(sf::RenderWindow * window)
{
	mapManager->ManageGraphic(window);
	player->Render(window);
	enemyManager->ManageGraphic(window);
	bulletManager->ManageGraphic(window);
	return Codes::Null;
}

int GameState::HandleInput(sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			player->SetDirection(Direction::Up);
			enemyManager->MovePlayer();
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			player->SetDirection(Direction::Down);
			enemyManager->MovePlayer();
		}
		else if (event.key.code == sf::Keyboard::Right)
		{
			player->SetDirection(Direction::Right);
			enemyManager->MovePlayer();
		}
		else if (event.key.code == sf::Keyboard::Left)
		{
			player->SetDirection(Direction::Left);
			enemyManager->MovePlayer();
		}
		else if (event.key.code == sf::Keyboard::Escape)
		{
			return Codes::GamePause;
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		player->Shoot();
	}
	return Codes::Null;
}

GameState::~GameState()
{
	delete player;
	delete playerTexture;
	delete mapManager;
	delete enemyManager;
	delete bulletManager;
}