#include "LoseState.h"

LoseState::LoseState() : kenvector(new sf::Font()), panelTexture(new sf::Texture()), freeTexture(new sf::Texture()), selectedTexture(new sf::Texture())
{
	panelTexture->loadFromFile("gui/panel.png");
	kenvector->loadFromFile("data/fnt/menufont.ttf");

	freeTexture->loadFromFile("gui/buttonnotselected.png");
	selectedTexture->loadFromFile("gui/buttonselected.png");

	panel = new Sprite(panelTexture);
	label = new Text("Przegrales", kenvector);
	continueButton = new Button(freeTexture, selectedTexture, "Kontynuuj", kenvector, 20);

	panel->SetScale(sf::Vector2f(3.5f, 2.f));
	panel->SetPosition(sf::Vector2f((800.f - panel->GetGlobalBounds().width) / 2.f, (600.f - panel->GetGlobalBounds().height) / 2.f));

	label->SetCharacterSize(29);
	sf::Vector2f position(0.f, 0.f);
	position.x += panel->GetGlobalBounds().width / 2 + panel->GetGlobalBounds().left;
	position.x -= label->GetGlobalBounds().width / 2;
	position.y += panel->GetGlobalBounds().height / 2 + panel->GetPosition().top - 50;
	position.y -= label->GetGlobalBounds().height / 2;
	label->SetPosition(position);

	position.x = 0;
	position.y = 0;
	position.x += panel->GetGlobalBounds().width / 2 + panel->GetPosition().left;
	position.y += panel->GetGlobalBounds().height / 2 + panel->GetPosition().top + 50;
	position.y -= continueButton->GetGlobalBounds().height / 2;
	continueButton->SetPosition(position);
	scene.push_back(panel);
	scene.push_back(label);
	scene.push_back(continueButton);
}

LoseState::~LoseState()
{
	scene.clear();
	delete continueButton;
	delete label;
	delete kenvector;
	delete panelTexture;
	delete freeTexture;
	delete selectedTexture;
}

int LoseState::HandleInput(sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Escape))
		return Codes::GameToMenu;
}