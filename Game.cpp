#include "Game.h"

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	Game m_game;
	return EXIT_SUCCESS;
}

void Game::ProcessCode(int returnCode)
{
	if (returnCode == Codes::Null) return;
	else if (returnCode == Codes::GameStart)
	{
		delete currentState;
		savedState = new GameState(m_window);
		currentState = savedState;
		inputController = currentState;
	}
	else if (returnCode == Codes::GameLose)
	{
		delete currentState;
		currentState = new LoseState();
		inputController = currentState;
	}
	else if(returnCode == Codes::GameWin)
	{
		delete currentState;
		currentState = new WinState();
		inputController = currentState;
	}
	else if (returnCode == Codes::GameToMenu)
	{
		delete currentState;
		currentState = new MenuState();
		inputController = currentState;
	}
	else if (returnCode == Codes::GamePause)
	{
		currentState = new PauseState();
		inputController = currentState;
	}
	else if (returnCode == Codes::GameResume)
	{
		delete currentState;
		currentState = savedState;
		inputController = currentState;
	}
}

Game::Game() : m_window(new sf::RenderWindow(sf::VideoMode(800,600),"Tanks"))
{
	m_window->setFramerateLimit(30);
	currentState = new MenuState();
	inputController = currentState;
	sf::Event event;
	sf::Clock clock;
	clock.restart();
	while (m_window->isOpen())
	{
		while (m_window->pollEvent(event))
			ProcessCode(inputController->HandleInput(event));
		
		m_window->clear(sf::Color::White);
		currentState->ManageGraphic(m_window);
		m_window->display();

		ProcessCode(currentState->ProcessLogic(clock.getElapsedTime()));
		clock.restart();
	}
}


Game::~Game()
{
}