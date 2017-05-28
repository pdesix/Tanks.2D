#pragma once
#include <fstream>
#include <cstdlib>
#include "Interfaces.h"
#include "Drawables.h"
#include "MapObject.h"

class MapManager : public IGraphicManager
{
	std::vector<std::string> keys;
	std::vector<sf::Texture*> textures;
	void LoadTextures();
	void GenerateRandomObstacle();

public:
	bool CheckSpawn(sf::FloatRect position);
	std::vector<MapObject*> scene;
	void GenerateMap(sf::RenderWindow * window);
	bool CheckCollisions(sf::FloatRect player);
	void RegisterTexture(std::string key, sf::Texture * pointer) { keys.push_back(key); textures.push_back(pointer); }
	sf::Texture * GetTexture(std::string key) { for (unsigned int i = 0; i < keys.size(); i++) if (keys[i] == key) return textures[i]; throw std::exception("texture not loaded"); }

	MapManager();
	~MapManager();

	inline virtual int ManageGraphic(sf::RenderWindow * window) override { for (auto & drawable : scene) drawable->Render(window); return 1; }
};