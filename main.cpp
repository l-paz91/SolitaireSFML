// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Solitaire

*/
// https://github.com/l-paz91/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "GameFacilities.h"
#include "GameManager.h"
#include "TextureManager.h"

#include <SFML/Graphics.hpp>

// -----------------------------------------------------------------------------

int main()
{
	using namespace sf;

	// create the main window, prevent it from being resized
	RenderWindow mainWindow(VideoMode(GameFacilities::gWindowWidth, GameFacilities::gWindowHeight), "Solitaire", sf::Style::Titlebar | sf::Style::Close);

	// set framerate
	mainWindow.setFramerateLimit(60);

	// clock for timing
	Clock clock;

	// create the background sprite
	Sprite backgroundSprite;
	backgroundSprite.setTexture(TextureManager::getTexture("Graphics/Background3.jpg"));

	// Set up Game Manager
	GameManager gameManager(mainWindow);
	gameManager.init();

	// start the game loop
	while (mainWindow.isOpen())
	{
		// Handle Timing
		Time dt = clock.restart();

		// ---- PROCESS EVENTS ----------------------------------------------------- //
		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				mainWindow.close();
			}

			// process game events
			gameManager.processEvents(event);
		}

		// ---- CLEAR SCREEN ------------------------------------------------------- //
		mainWindow.clear();

		// ---- UPDATE ------------------------------------------------------------- //
		gameManager.update(dt);

		// ---- RENDER ------------------------------------------------------------- //
		mainWindow.draw(backgroundSprite);
		gameManager.render();

		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		mainWindow.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------