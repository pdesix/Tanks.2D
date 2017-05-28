#pragma once
#include "Enemy.h"
#include "Player.h"
#include "EnemyLogic.h"

class EnemyManager : public IGraphicManager, public ILogicProcessor
{
	std::vector<Enemy*> enemies;
	std::vector<Sprite*> smokes;
	std::vector<std::thread*> deletors;

	MapManager * mapManager;
	BulletManager * bulletManager;
	Player * player;

	sf::Texture * redTexture;
	sf::Texture * greenTexture;
	sf::Texture * blueTexture;
	sf::Texture * bulletTextures[3];
	sf::Texture * smokeTexture;

public:
	EnemyManager(MapManager * mapMngr, BulletManager * bulletMngr, Player * playerPtr);
	~EnemyManager();
	virtual int ManageGraphic(sf::RenderWindow * window) override { for (Enemy * enemy : enemies) enemy->Render(window); for (Sprite * smoke : smokes) smoke->Render(window); return Codes::Null; }
	virtual int ProcessLogic(sf::Time deltaTime) override;
	virtual void MovePlayer();
	virtual void DeleteSmoke(Sprite * smoke);

	virtual void MakeDecision(Enemy * character);
};