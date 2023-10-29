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
}

// -----------------------------------------------------------------------------

GameManager::~GameManager()
{

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
		// are we hovering over stock?
		if (mDeck.isMouseOverStock(mousePosition))
		{
			mDeck.draw();
		}

		// is the stock empty?
		if (mBlankSpace.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)) 
			&& mDeck.isStockEmpty())
		{
			mDeck.reset();
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
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------