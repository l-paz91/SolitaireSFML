// -----------------------------------------------------------------------------
#ifndef StatusBar_H
#define StatusBar_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "ScoringSystem.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

// -----------------------------------------------------------------------------

/*
	// ---- Status Bar ----//

	This is the status bar that appears at the bottom of the window. It displays
	how long the current game of solitaire has been going on for, how many moves
	have been made, and the current score.

*/

// -----------------------------------------------------------------------------

class StatusBar
{
public:
	StatusBar();
	~StatusBar() {}

	void update(float pDeltaTimeAsSeconds);
	void render(sf::RenderWindow& pWindow);

	void setScore(EScoringSystem pScoreType);
	void decrementScore(int pAmount);
	void incrementMoves();
	void startTimer() { mTime = 0.f; }

	int getScore() { return mScore; }
	int getMoves() { return mMoves; }
	float getTime() { return mTime; }

private:
	sf::RectangleShape mStatusBar;
	sf::Font mFont;
	sf::Text mScoreText;
	sf::Text mMovesText;
	sf::Text mTimeText;

	int mScore;
	int mMoves;
	float mTime;
};


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !StatusBar_H