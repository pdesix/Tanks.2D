#pragma once
#include "Interfaces.h"
#include "Drawables.h"

class MenuState : public IState
{
	sf::Texture * logoTexture;
	Sprite * logo;

	sf::Texture * textureSelected;
	sf::Texture * textureNotSelected;
	sf::Font * menuFont;

	sf::Texture * panelTexture;
	Sprite * panel;

	std::vector<Button*> options;
	std::vector<IRenderable*> scene;
	int selectedID;

public:
	MenuState();

	inline virtual int ManageGraphic(sf::RenderWindow * window) override { window->clear(sf::Color::White); for (auto & drawable : scene) drawable->Render(window); return 1; }
	virtual int HandleInput(sf::Event & event) override;
	inline virtual int ProcessLogic(sf::Time deltaTime) override { return Codes::Null; };
};