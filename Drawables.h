#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

class IRenderable
{
public:
	virtual void Render(sf::RenderWindow * target) = 0;
	virtual void Move(sf::Vector2f & position) = 0;
	virtual void SetPosition(sf::Vector2f & position) = 0;
	virtual sf::FloatRect GetPosition() = 0;
	virtual sf::FloatRect GetGlobalBounds() = 0;
};

class Text : public IRenderable
{
protected:
	sf::Text * text;
	sf::Font * font;
	std::string label;

public:
	Text(std::string xlabel, sf::Font * xfont) : font(xfont), label(xlabel), text(new sf::Text(sf::String(xlabel), *xfont)) { text->setOutlineColor(sf::Color::Black); text->setOutlineThickness(0.5); }
	Text::Text() { delete text; }
	inline virtual void Render(sf::RenderWindow * target) override { target->draw(*text); }
	inline virtual void Move(sf::Vector2f & position) override { text->move(position); }
	inline virtual void SetPosition(sf::Vector2f & position) override { text->setPosition(position); }
	inline virtual sf::FloatRect GetPosition() override { return text->getGlobalBounds(); }
	inline virtual void SetFont(sf::Font * xfont) { font = xfont; }
	inline float GetWidth() { return text->getGlobalBounds().width; }
	inline virtual sf::FloatRect GetGlobalBounds() override { return text->getGlobalBounds(); }
	inline void SetCharacterSize(unsigned int size) { text->setCharacterSize(size); }
};

class Sprite : public IRenderable
{
protected:
	sf::Texture * texture;
	sf::Sprite * sprite;

public:
	Sprite(sf::Texture * text) : texture(text), sprite(new sf::Sprite(*text)) { }
	virtual ~Sprite() { delete sprite; }
	inline virtual void Render(sf::RenderWindow * target) override { target->draw(*sprite); }
	inline virtual void Move(sf::Vector2f & position) override { sprite->move(position); }
	inline virtual void SetPosition(sf::Vector2f & position) override { sprite->setPosition(position); }
	inline virtual sf::FloatRect GetPosition() override { return sprite->getGlobalBounds(); }
	inline virtual void SetTexture(sf::Texture * text) { texture = text; }
	inline virtual void SetScale(sf::Vector2f & size) { sprite->setScale(size); }
	inline virtual void SetRotation(float angle) { sprite->setRotation(angle); }
	inline virtual sf::FloatRect GetGlobalBounds() override { return sprite->getGlobalBounds(); }
};

class Button : public Sprite
{
protected:
	bool ifSelected;
	sf::Texture * textureFree;
	Text * label;

public:
	Button::Button(sf::Texture * free, sf::Texture * select, std::string labeltext, sf::Font * font, unsigned int characterSize = 30);
	Button::~Button() { delete label; Sprite::~Sprite(); }
	inline virtual void NoteSelectionChange();
	inline virtual void SetTextureFree(sf::Texture * text) { textureFree = text; }
	inline virtual void Render(sf::RenderWindow * target) { Sprite::Render(target); label->Render(target); }
	inline virtual void SetPosition(sf::Vector2f & position);
};