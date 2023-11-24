// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "StatusBar.h"

#include "GameFacilities.h"

// -----------------------------------------------------------------------------

StatusBar::StatusBar()
	: mStatusBar(sf::Vector2f(GameFacilities::gWindowWidth, 20.f))
	, mFont(GameFacilities::getIMFellFrenchCannonFont())
	, mScoreText("Score 0", mFont, 16)
	, mMovesText("Moves 0", mFont, 16)
	, mTimeText("Time ", mFont, 16)
	, mScore(0)
	, mMoves(0)
	, mTime(0)
{
	mStatusBar.setFillColor(sf::Color(66, 66, 66, 200)); // grey
	mStatusBar.setPosition(0.f, GameFacilities::gWindowHeight - mStatusBar.getSize().y);

	mScoreText.setFillColor(sf::Color(200, 200, 200));
	mScoreText.setPosition(10.f, GameFacilities::gWindowHeight - mStatusBar.getSize().y);

	mMovesText.setFillColor(sf::Color::Black);
	mMovesText.setPosition(400.f, GameFacilities::gWindowHeight - mStatusBar.getSize().y);

	mTimeText.setFillColor(sf::Color::Black);
	mTimeText.setPosition(700.f, GameFacilities::gWindowHeight - mStatusBar.getSize().y);
}

// -----------------------------------------------------------------------------

void StatusBar::update(float pDeltaTimeAsSeconds, EScoringSystem pScoreType)
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

void StatusBar::setScore(EScoringSystem pScoreType)
{
	mScore += static_cast<int>(pScoreType);
	mScoreText.setString("Score " + std::to_string(mScore));
}

// -----------------------------------------------------------------------------

void StatusBar::decrementScore(int pAmount)
{
	mScore -= pAmount;
	mScoreText.setString("Score " + std::to_string(mScore));
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------