#pragma once
#include "Interfaces.h"
#include "EnemyManager.h"
#include "Player.h"

class GameState : public IState
{
	MapManager * mapManager;
	BulletManager * bulletManager;
	EnemyManager * enemyManager;

	sf::Texture * playerTexture;
	Player * player;

	sf::RenderWindow * renderWindow;

public:
	GameState(sf::RenderWindow * rWindow);
	~GameState();

	virtual int ManageGraphic(sf::RenderWindow * window) override;
	virtual int HandleInput(sf::Event & event) override;
	virtual int ProcessLogic(sf::Time deltaTime) override;
};