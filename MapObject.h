#pragma once
#include "Drawables.h"

class MapObject : public Sprite
{
	bool isCollidable;

public:
	MapObject(sf::Texture * text, bool stepable);
	~MapObject();
	inline bool IfCollidable() { return isCollidable; }
};

