#pragma once
#include "Drawables.h"
#include "Bullet.h"
#include "Interfaces.h"
#include "MapManager.h"

class BulletManager : public IGraphicManager, public ILogicProcessor
{
	std::vector<Bullet*> bullets;
	sf::Texture * playerBullet;
	MapManager * mapManager;
	bool CheckCollisions(Bullet * bullet);
	
public:
	enum SourceType
	{
		SourcePlayer
	};

	void RegisterBullet(sf::Vector2f pos, Direction dir, SourceType source);
	void RegisterBullet(sf::Vector2f pos, Direction dir, sf::Texture * bulletTexture);
	BulletManager(MapManager * mngr);
	~BulletManager();
	virtual int ManageGraphic(sf::RenderWindow * window) override { for (auto & drawable : bullets) drawable->Render(window); return 1; }
	virtual int ProcessLogic(sf::Time deltaTime) override;
	static constexpr float GetBulletHeight() { return 34; }
	static constexpr float GetBulletWidth() { return 20; }
	bool CheckCharacterCollision(sf::FloatRect playerPos);
};

