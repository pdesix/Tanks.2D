#pragma once
#include "Drawables.h"
#include "Interfaces.h"

class EnemyLogic
{
public:
	static int GetDirection(sf::FloatRect from, sf::FloatRect to);
};