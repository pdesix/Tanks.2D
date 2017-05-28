#include "Drawables.h"

Button::Button(sf::Texture * free, sf::Texture * select, std::string labeltext, sf::Font * font, unsigned int characterSize) : Sprite(select), textureFree(free), label(new Text(labeltext,font))
{
	ifSelected = true;
	label->SetCharacterSize(characterSize);
}

void Button::SetPosition(sf::Vector2f & position)
{
	sf::Vector2f posCopy(position);
	posCopy.x -= label->GetWidth() / 2;
	posCopy.y += (sprite->getGlobalBounds().height) / 2 - label->GetGlobalBounds().height;
	label->SetPosition(posCopy);

	position.x -= sprite->getGlobalBounds().width / 2;
	Sprite::SetPosition(position);
}

void Button::NoteSelectionChange()
{
	if (ifSelected)
	{
		sprite->setTexture(*textureFree);
		ifSelected = false;
	}
	else
	{
		sprite->setTexture(*texture);
		ifSelected = true;
	}
}