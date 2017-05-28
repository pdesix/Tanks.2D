#include "MapManager.h"

MapManager::MapManager()
{
	LoadTextures();
}

MapManager::~MapManager()
{
	for (MapObject * object : scene)
		delete object;
	for (sf::Texture * texture : textures)
		delete texture;
}

bool MapManager::CheckSpawn(sf::FloatRect position)
{
	for (unsigned int i = 1; i < scene.size(); i++)
	{
		if (position.intersects(scene[i]->GetGlobalBounds()))
			return true;
	}
	return false;
}

bool MapManager::CheckCollisions(sf::FloatRect player)
{
	for (unsigned int i = 1; i < scene.size(); i++)
	{
		if (scene[i]->IfCollidable() && scene[i]->GetGlobalBounds().intersects(player))
			return true;
	}
	return false;
}

void MapManager::GenerateMap(sf::RenderWindow * window)
{
	MapObject * mapElement = new MapObject(GetTexture("Enviroinment - Dirt"),true);
	mapElement->SetPosition(sf::Vector2f(0.f, 0.f));
	mapElement->SetScale(sf::Vector2f(800.f / 128.f, 600.f / 128.f));
	scene.push_back(mapElement);
	
	// Generating rams
	sf::Texture * sandBag = GetTexture("Obstacles - Sand Bag");
	for (int i = 0; i < 15; i++)
	{
		mapElement = new MapObject(sandBag, false);
		mapElement->SetScale(sf::Vector2f(42.f / 66.f, 0.7f));
		mapElement->SetRotation(90);
		mapElement->SetPosition(sf::Vector2f(mapElement->GetPosition().width, (i - 1)*mapElement->GetPosition().height + 25));
		scene.push_back(mapElement);
	}
	for (int i = 0; i < 15; i++)
	{
		mapElement = new MapObject(sandBag, false);
		mapElement->SetScale(sf::Vector2f(42.f / 66.f, 0.7f));
		mapElement->SetRotation(90);
		mapElement->SetPosition(sf::Vector2f(800.f, (i - 1)*mapElement->GetPosition().height + 25));
		scene.push_back(mapElement);
	}
	for (int i = 0; i < 20; i++)
	{
		mapElement = new MapObject(sandBag, false);
		mapElement->SetScale(sf::Vector2f(42.f / 66.f, 0.6f));
		mapElement->SetPosition(sf::Vector2f(40.f * i, 0.f));
		scene.push_back(mapElement);
	}
	for (int i = 0; i < 20; i++)
	{
		mapElement = new MapObject(sandBag, false);
		mapElement->SetScale(sf::Vector2f(42.f / 66.f, 0.7f));
		mapElement->SetPosition(sf::Vector2f(40.f * i, 600.f - mapElement->GetPosition().height));
		scene.push_back(mapElement);
	}

	for (int i = 0; i < 10; i++)
	{
		GenerateRandomObstacle();
	}

	ManageGraphic(window);
}

void MapManager::GenerateRandomObstacle()
{
	MapObject * mapElement;
	int j = 3 + rand() % 3;
	mapElement = new MapObject(GetTexture(keys[j]), false);
	for (;;)
	{
		bool crossed = false;
		mapElement->SetPosition(sf::Vector2f(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600)));
		mapElement->SetRotation(static_cast<float>(rand() % 360));
		for (unsigned int i = 1; i < scene.size(); i++)
		{
			if (scene[i]->GetGlobalBounds().intersects(mapElement->GetGlobalBounds()))
				crossed = true;
		}
		if (!crossed) break;
	}
	mapElement->SetScale(sf::Vector2f(0.75f, 0.75f));
	scene.push_back(mapElement);
	return;
}

void MapManager::LoadTextures()
{
	sf::Texture * loadingPointer; 

	// TODO: add obstacles
	loadingPointer = new sf::Texture;
	loadingPointer->loadFromFile("env/dirt.png");
	RegisterTexture("Enviroinment - Dirt", loadingPointer);

	loadingPointer = new sf::Texture;
	loadingPointer->loadFromFile("env/grass.png");
	RegisterTexture("Enviroinment - Grass", loadingPointer);

	loadingPointer = new sf::Texture;
	loadingPointer->loadFromFile("env/sand.png");
	RegisterTexture("Enviroinment - Sand", loadingPointer);

	loadingPointer = new sf::Texture;
	loadingPointer->loadFromFile("env/treeSmall.png");
	RegisterTexture("Enviroinment - Small Tree", loadingPointer);

	loadingPointer = new sf::Texture;
	loadingPointer->loadFromFile("env/treeLarge.png");
	RegisterTexture("Enviroinment - Small Large", loadingPointer);

	loadingPointer = new sf::Texture;
	loadingPointer->loadFromFile("obst/sandBagBrown.png");
	RegisterTexture("Obstacles - Sand Bag Brown", loadingPointer);

	loadingPointer = new sf::Texture;
	loadingPointer->loadFromFile("obst/sandBag.png");
	RegisterTexture("Obstacles - Sand Bag", loadingPointer);


}