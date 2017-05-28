#include "MenuState.h"

MenuState::MenuState() : menuFont(new sf::Font), panelTexture(new sf::Texture), 
	textureNotSelected(new sf::Texture), textureSelected(new sf::Texture),
	logoTexture(new sf::Texture)
{
	logoTexture->loadFromFile("gui/logo.png");
	logo = new Sprite(logoTexture);
	scene.push_back(logo);


	panelTexture->loadFromFile("gui/panel.png");
	panel = new Sprite(panelTexture);
	panel->SetScale(sf::Vector2f(3.5f, 2.f));
	panel->SetPosition(sf::Vector2f((800.f - panel->GetGlobalBounds().width) / 2.f, (600.f - panel->GetGlobalBounds().height) / 2.f));
	scene.push_back(panel);

	sf::Vector2f position(0.f, 0.f);
	position.x += (800 - logo->GetGlobalBounds().width) / 2;
	position.y += 15;
	logo->SetPosition(position);

	textureNotSelected->loadFromFile("gui/buttonnotselected.png");
	textureSelected->loadFromFile("gui/buttonselected.png");
	menuFont->loadFromFile("data/fnt/menufont.ttf");

	options.push_back(new Button(textureNotSelected, textureSelected, "Graj", menuFont));
	scene.push_back(options[0]);

	position.x = 0;
	position.y = 0;
	position.x += panel->GetGlobalBounds().width / 2 + panel->GetPosition().left;
	position.y += panel->GetGlobalBounds().height / 2 + panel->GetPosition().top;
	position.y -= options[0]->GetGlobalBounds().height / 2;
	options[0]->SetPosition(position);

	selectedID = 0;
}

int MenuState::HandleInput(sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			selectedID--;
			if (selectedID < 0)
			{
				options[0]->NoteSelectionChange();
				selectedID = options.size() - 1;
				options[selectedID]->NoteSelectionChange();
			}
			else
			{
				options[selectedID]->NoteSelectionChange();
				options[selectedID+1]->NoteSelectionChange();
			}
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			selectedID++;
			if (static_cast<unsigned int>(selectedID) >= options.size())
			{
				options[options.size()-1]->NoteSelectionChange();
				selectedID = 0;
				options[selectedID]->NoteSelectionChange();
			}
			else
			{
				options[selectedID]->NoteSelectionChange();
				options[selectedID-1]->NoteSelectionChange();
			}
		}
		else if (event.key.code == sf::Keyboard::Return)
		{
			if (selectedID == 0)
				return Codes::GameStart;
		}
	}
	return Codes::Null;
}