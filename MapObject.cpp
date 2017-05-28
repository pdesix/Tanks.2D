#include "MapObject.h"

MapObject::MapObject(sf::Texture * text, bool stepable) : Sprite::Sprite(text), isCollidable(!stepable)
{
}


MapObject::~MapObject()
{
	Sprite::~Sprite();
}
