#pragma once
#include "Interfaces.h"
#include "Drawables.h"

class WinState : public IState
{
	std::vector<IRenderable*> scene;
	sf::Texture * panelTexture;
	sf::Texture * freeTexture;
	sf::Texture * selectedTexture;
	sf::Font * kenvector;

	Sprite * panel;
	Text * label;
	Button * continueButton;

public:
	WinState();
	~WinState();

	inline virtual int ManageGraphic(sf::RenderWindow * window) override { for (auto & drawable : scene) drawable->Render(window); return 1; }
	virtual int HandleInput(sf::Event & event) override;
	inline virtual int ProcessLogic(sf::Time deltaTime) override { return Codes::Null; };
};
