#include "EnemyLogic.h"

int EnemyLogic::GetDirection(sf::FloatRect from, sf::FloatRect to)
{
	sf::FloatRect vertical(from.left, 0, from.width, 600);
	sf::FloatRect horizontal(0, from.top, 800, from.height);
	if (to.intersects(vertical))
		if (to.top > horizontal.top + horizontal.height)
			return Down;
		else return Up;
	else if (to.intersects(horizontal))
		if (to.left > vertical.left + vertical.width)
			return Right;
		else return Left;
	else
		return Wrong;
}