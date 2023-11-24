// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "StatusBar.h"

#include "GameFacilities.h"

#include <iomanip>
#include <sstream>

// -----------------------------------------------------------------------------

StatusBar::StatusBar()
	: mStatusBar(sf::Vector2f(GameFacilities::gWindowWidth, 20.f))
	, mFont(GameFacilities::getIMFellFrenchCannonFont())
	, mScoreText("0", mFont, 16)
	, mMovesText("0", mFont, 16)
	, mTimeText("0:00", mFont, 16)
	, mScore(0)
	, mMoves(0)
	, mTime(0)
{
	mStatusBar.setFillColor(sf::Color(66, 66, 66, 200)); // grey
	mStatusBar.setPosition(0.f, GameFacilities::gWindowHeight - mStatusBar.getSize().y);

	mScoreText.setFillColor(sf::Color(200, 200, 200));
	mScoreText.setPosition(10.f, GameFacilities::gWindowHeight - mStatusBar.getSize().y - 2);

	mMovesText.setFillColor(sf::Color(200, 200, 200));
	mMovesText.setPosition(750.f, GameFacilities::gWindowHeight - mStatusBar.getSize().y - 2);

	mTimeText.setFillColor(sf::Color(200, 200, 200));
	mTimeText.setPosition(850.f, GameFacilities::gWindowHeight - mStatusBar.getSize().y - 2);
}

// -----------------------------------------------------------------------------

void StatusBar::update(float pDeltaTimeAsSeconds)
{
	mTime += pDeltaTimeAsSeconds;

	// calculate minutes and seconds
	int totalSeconds = static_cast<int>(mTime);
	int minutes = totalSeconds / 60;
	int seconds = totalSeconds % 60;

	// create a stringstream for formatting
	std::stringstream timeStream;

	// use setfill and setw to format the output like "00:00"
	timeStream << std::setfill('0') << std::setw(2) << minutes << ":"
			   << std::setfill('0') << std::setw(2) << seconds;

	mTimeText.setString(timeStream.str());
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
	mScoreText.setString(std::to_string(mScore));
}

// -----------------------------------------------------------------------------

void StatusBar::decrementScore(int pAmount)
{
	mScore -= pAmount;
	mScoreText.setString(std::to_string(mScore));
}

// -----------------------------------------------------------------------------

void StatusBar::incrementMoves()
{
	++mMoves;
	mMovesText.setString(std::to_string(mMoves));
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------