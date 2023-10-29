// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Solitaire

*/
// https://github.com/l-paz91/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

// -----------------------------------------------------------------------------

int main()
{
	using namespace sf;

	// create the main window, prevent it from being resized
	RenderWindow mainWindow(VideoMode(1024, 768), "SFML Works", sf::Style::Titlebar | sf::Style::Close);

	// debug start
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	// set framerate
	mainWindow.setFramerateLimit(60);

	// clock for timing
	Clock clock;

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

		}

		// ---- CLEAR SCREEN ------------------------------------------------------- //
		mainWindow.clear();

		// ---- UPDATE ------------------------------------------------------------- //

		// ---- RENDER ------------------------------------------------------------- //
		mainWindow.draw(shape);

		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		mainWindow.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------