#include "PauseState.h"

PauseState::PauseState() : continueButton(), menuButton(),
	panelTexture(new sf::Texture()), freeTexture(new sf::Texture()), selectedTexture(new sf::Texture()),
	kenvector(new sf::Font()), selectedID(0)
{
	kenvector->loadFromFile("data/fnt/menufont.ttf");
	panelTexture->loadFromFile("gui/panel.png");
	selectedTexture->loadFromFile("gui/buttonselected.png");
	freeTexture->loadFromFile("gui/buttonnotselected.png");

	panel = new Sprite(panelTexture); 
	continueButton = new Button(freeTexture, selectedTexture, "Kontynuuj", kenvector, 20);
	menuButton = new Button(freeTexture, selectedTexture, "Menu", kenvector, 20);
	label = new Text("PAUZA", kenvector);

	panel->SetScale(sf::Vector2f(3.5f, 2.f));
	panel->SetPosition(sf::Vector2f((800.f - panel->GetGlobalBounds().width) / 2.f, (600.f - panel->GetGlobalBounds().height) / 2.f));
	scene.push_back(panel);

	label->SetCharacterSize(29);
	sf::Vector2f position(0.f, 0.f);
	position.x += panel->GetGlobalBounds().width / 2 + panel->GetGlobalBounds().left;
	position.x -= label->GetGlobalBounds().width / 2;
	position.y += panel->GetGlobalBounds().height / 2 + panel->GetPosition().top - 70;
	position.y -= label->GetGlobalBounds().height / 2;
	label->SetPosition(position);
	scene.push_back(label);

	position.x = 0;
	position.y = 0;
	position.x += panel->GetGlobalBounds().width / 2 + panel->GetPosition().left;
	position.y += panel->GetGlobalBounds().height / 2 + panel->GetPosition().top - 10;
	position.y -= continueButton->GetGlobalBounds().height / 2;
	continueButton->SetPosition(position);
	scene.push_back(continueButton);

	position.x = 0;
	position.y = 0;
	position.x += panel->GetGlobalBounds().width / 2 + panel->GetPosition().left;
	position.y += panel->GetGlobalBounds().height / 2 + panel->GetPosition().top - 10;
	position.y -= continueButton->GetGlobalBounds().height / 2;
	position.y += continueButton->GetGlobalBounds().height / 2;
	position.y += 35.f;
	menuButton->SetPosition(position);
	scene.push_back(menuButton);

	menuButton->NoteSelectionChange();
}


PauseState::~PauseState()
{
}

void PauseState::NoticeSelectionChange()
{
	continueButton->NoteSelectionChange();
	menuButton->NoteSelectionChange();
	if (selectedID == 0)
		selectedID = 1;
	else
		selectedID = 0;
}

int PauseState::HandleInput(sf::Event & input)
{
	if (input.type == sf::Event::KeyPressed)
		if (input.key.code == sf::Keyboard::Escape)
		{
			return Codes::GameToMenu;
		}
		else if (input.key.code == sf::Keyboard::Return)
		{
			if (selectedID == 0)
				return Codes::GameResume;
			else
				return Codes::GameToMenu;
		}
		else if (input.key.code == sf::Keyboard::Up || input.key.code == sf::Keyboard::Down)
		{
			NoticeSelectionChange();
			return Codes::Null;
		}
	return Codes::Null;
}