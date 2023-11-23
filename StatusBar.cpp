// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "StatusBar.h"

#include "GameFacilities.h"

// -----------------------------------------------------------------------------

StatusBar::StatusBar()
	: mStatusBar(sf::Vector2f(GameFacilities::gWindowWidth, 20.f))
	, mFont(GameFacilities::getRobotoRegularFont())
	, mScoreText("Score: ", mFont, 20)
	, mMovesText("Moves: ", mFont, 20)
	, mTimeText("Time: ", mFont, 20)
	, mScore(0)
	, mMoves(0)
	, mTime(0)
{
	mStatusBar.setFillColor(sf::Color(66, 66, 66, 200)); // grey
	mStatusBar.setPosition(0.f, GameFacilities::gWindowHeight - mStatusBar.getSize().y);

	mScoreText.setFillColor(sf::Color::Black);
	mScoreText.setPosition(10.f, GameFacilities::gWindowHeight - mStatusBar.getSize().y);

	mMovesText.setFillColor(sf::Color::Black);
	mMovesText.setPosition(400.f, GameFacilities::gWindowHeight - mStatusBar.getSize().y);

	mTimeText.setFillColor(sf::Color::Black);
	mTimeText.setPosition(700.f, GameFacilities::gWindowHeight - mStatusBar.getSize().y);
}

// -----------------------------------------------------------------------------

void StatusBar::update(float pDeltaTimeAsSeconds)
{

}

// -----------------------------------------------------------------------------

void StatusBar::render(sf::RenderWindow& pWindow)
{
	pWindow.draw(mStatusBar);

	pWindow.draw(mScoreText);
	pWindow.draw(mMovesText);
	pWindow.draw(mTimeText);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------