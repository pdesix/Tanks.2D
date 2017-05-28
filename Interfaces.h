#pragma once
#include <SFML\Graphics.hpp>

enum Direction
{
	Left,
	Up,
	Right,
	Down,
	Wrong
};

enum Codes
{
	Null,
	GameStart,
	GameLose,
	GameWin,
	GameError,
	GameToMenu,
	GamePause,
	GameResume
};

class IInputController
{
public:
	virtual int HandleInput(sf::Event & event) = 0;
};

class IGraphicManager
{
public:
	virtual int ManageGraphic(sf::RenderWindow * window) = 0;
};

class ILogicProcessor
{
public:
	virtual int ProcessLogic(sf::Time deltaTime) = 0;
};

class IState: public IInputController, public IGraphicManager, public ILogicProcessor
{
public:
	virtual int ManageGraphic(sf::RenderWindow * window) = 0;
	virtual int HandleInput(sf::Event & event) = 0;
	virtual int ProcessLogic(sf::Time deltaTime) = 0;
};