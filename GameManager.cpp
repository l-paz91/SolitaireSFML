// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "GameManager.h"
#include "TextureManager.h"

#include <SFML/Window/Event.hpp>

// -----------------------------------------------------------------------------

GameManager::GameManager(sf::RenderWindow& pWindow)
	: mWindowRef(pWindow)
{
	// set up card back sprite
	mCardBackSprite.setTexture(TextureManager::getTexture("Graphics/BackDesign.png"));
	mCardBackSprite.setScale(0.2f, 0.2f);
	mCardBackSprite.setPosition(20.f, 20.f);

	// set up the blank space
	mBlankSpace.setSize(sf::Vector2f(mCardBackSprite.getGlobalBounds().width, mCardBackSprite.getGlobalBounds().height));
	mBlankSpace.setFillColor(sf::Color(111, 78, 55));
	mBlankSpace.setPosition(20.f, 20.f);

	// set up the tableau piles
	constexpr float tableauStart = 20.f;
	constexpr float tableauWidth = 140.f;
	constexpr float tableauHeight = 200.f;

	for (int i = 0; i < 7; ++i)
	{
		float tableauX = tableauStart + (tableauWidth * i);
		mTableaus.push_back(Tableau(sf::Vector2f(tableauX, tableauHeight)));
	}
}

// -----------------------------------------------------------------------------

GameManager::~GameManager()
{

}

// -----------------------------------------------------------------------------

void GameManager::init()
{
	beginGame();
}

// -----------------------------------------------------------------------------

void GameManager::processEvents(const sf::Event& pEvent)
{
	using namespace sf;
	const Vector2i mousePosition = Mouse::getPosition(mWindowRef);

	// process card events


	// LMB pressed
	if (pEvent.type == Event::MouseButtonPressed && pEvent.mouseButton.button == Mouse::Left)
	{

	}

	// LMB released
	if (pEvent.type == Event::MouseButtonReleased && pEvent.mouseButton.button == Mouse::Left)
	{
		// is the stock empty?
		if (mBlankSpace.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)) 
			&& mDeck.isStockEmpty())
		{
			mDeck.reset();
		}

		// are we hovering over stock?
		if (mDeck.isMouseOverStock(mousePosition))
		{
			mDeck.draw();
		}
	}
}

// -----------------------------------------------------------------------------

void GameManager::update(sf::Time& pDeltaTime)
{
	const float deltaTimeSeconds = pDeltaTime.asSeconds();

}

// -----------------------------------------------------------------------------

void GameManager::render()
{
	mWindowRef.draw(mBlankSpace);

	// render the deck pile (stock and waste)
	mDeck.render(mWindowRef);

	// render the tableau piles
	for (int i = 0; i < 7; ++i)
	{
		mTableaus[i].render(mWindowRef);
	}
}

// -----------------------------------------------------------------------------

void GameManager::beginGame()
{
	// deal cards to tableau piles from the deck
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < i + 1; ++j)
		{
			// deal cards from the deck to the tableau piles
			mTableaus[i].push(mDeck.peekStock());
			mDeck.popStock();
		}
	}

	// flip the top card of each tableau pile
	for (int i = 0; i < 7; ++i)
	{
		mTableaus[i].peek()->flip();
	}

	// print the tableau piles
	for (int i = 0; i < 7; ++i)
	{
		mTableaus[i].printToConsole();
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------