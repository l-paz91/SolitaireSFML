// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "GameManager.h"
#include "TextureManager.h"

#include <SFML/Window/Event.hpp>

// -----------------------------------------------------------------------------

GameManager::GameManager(sf::RenderWindow& pWindow)
	: mCard(ECardRank::eACE, ECardSuit::eSPADES, false, "Graphics/Spades/1.png")
	, mWindowRef(pWindow)
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
	const Vector2f mousePosition = static_cast<Vector2f>(Mouse::getPosition(mWindowRef));

	// process card events
	mCard.processEvents(pEvent);

	// LMB pressed
	if (pEvent.type == Event::MouseButtonPressed && pEvent.mouseButton.button == Mouse::Left)
	{

	}

	// LMB released
	if (pEvent.type == Event::MouseButtonReleased && pEvent.mouseButton.button == Mouse::Left)
	{
		// if mouse if hovering over the card and released, flip it
		if (mCardBackSprite.getGlobalBounds().contains(mousePosition))
		{
			mCard.flip();
		}
	}
}

// -----------------------------------------------------------------------------

void GameManager::update(sf::Time& pDeltaTime)
{
	const float deltaTimeSeconds = pDeltaTime.asSeconds();

	// update card
	mCard.update(pDeltaTime, mWindowRef);
}

// -----------------------------------------------------------------------------

void GameManager::render()
{
	mWindowRef.draw(mBlankSpace);
	mCard.render(mWindowRef);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------