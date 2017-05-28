#pragma once
#include <iostream>
#include <cstdlib>
#include <SFML\Graphics.hpp>
#include "Interfaces.h"
#include "MenuState.h"
#include "GameState.h"
#include "LoseState.h"
#include "PauseState.h"
#include "WinState.h"

int main();

class Game
{
	sf::RenderWindow * m_window;
	IState * currentState;
	GameState * savedState;
	IInputController * inputController;
	void ProcessCode(int returnCode);

public:
	Game();
	~Game();
};