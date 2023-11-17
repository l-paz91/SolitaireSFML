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
	backgroundSprite.setTexture(TextureManager::getTexture("Graphics/Background4.png"));

	// create the render texture for the win screen
	RenderTexture winScreenBufferA;
	winScreenBufferA.create(GameFacilities::gWindowWidth, GameFacilities::gWindowHeight);

	RenderTexture winScreenBufferB;
	winScreenBufferB.create(GameFacilities::gWindowWidth, GameFacilities::gWindowHeight);

	RenderTexture* currentWinScreenBuffer = &winScreenBufferA;
	RenderTexture* prevWinScreenBuffer = &winScreenBufferB;

	Sprite currentWinScreenSprite;
	Sprite prevWinScreenSprite;

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

		// ---- UPDATE ------------------------------------------------------------- //
		gameManager.update(dt);

		// ---- CLEAR SCREEN ------------------------------------------------------- //
		if (gameManager.getGameState() == EGameState::ePLAYING)
		{
			mainWindow.clear();
		}

		// ---- RENDER ------------------------------------------------------------- //

		if (gameManager.getGameState() == EGameState::ePLAYING)
		{
			mainWindow.draw(backgroundSprite);
			gameManager.render();
		}
		else if (gameManager.getGameState() == EGameState::eWON)
		{
			currentWinScreenBuffer->clear(Color(0, 0, 0, 0));

			// draw the previous buffer with transparency
			prevWinScreenSprite.setTexture(prevWinScreenBuffer->getTexture());
			//Sprite prevWinScreenSprite(prevWinScreenBuffer->getTexture());
			prevWinScreenSprite.setColor(Color(255, 255, 255, 255));
			currentWinScreenBuffer->draw(prevWinScreenSprite);

			// render current game state onto the buffer
			gameManager.renderWinAnimation(*currentWinScreenBuffer);

			// complete the current frame
			currentWinScreenBuffer->display();

			// swap buffers
			std::swap(currentWinScreenBuffer, prevWinScreenBuffer);

			currentWinScreenSprite.setTexture(currentWinScreenBuffer->getTexture());
			mainWindow.draw(currentWinScreenSprite);
		}
		else if(gameManager.getGameState() == EGameState::eEND)
		{
			mainWindow.draw(backgroundSprite);
			gameManager.render();
		}

		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		mainWindow.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------