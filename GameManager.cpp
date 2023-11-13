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
	mBlankSpace.setFillColor(sf::Color(27, 18, 18));
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

	// set up the foundation piles
	constexpr float foundationStart = 440.f;
	constexpr float foundationWidth = 140.f;
	constexpr float foundationHeight = 20.f;

	for (int i = 0; i < 4; ++i)
	{
		float foundationX = foundationStart + (foundationWidth * i);
		mFoundations.push_back(Foundation(sf::Vector2f(foundationX, foundationHeight)));
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
		if (Card* selectedCard = getCardAtMousePosition())
		{
			if (!mIsCardBeingDragged)
			{
				// start dragging the card
				mIsCardBeingDragged = true;
				mDraggedCardOriginalPile = findPileContainingCard(selectedCard);
				mDraggedCard = selectedCard;
				mDraggedCardOriginalPosition = mDraggedCard->getSprite().getPosition();

				mDraggedCardOffset = mDraggedCardOriginalPosition - static_cast<sf::Vector2f>(mousePosition);
			}
		}
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
		if (mDeck.isMouseOverStock(mousePosition) && !mIsCardBeingDragged)
		{
			mDeck.draw();
		}

		// are dragging a card and releasing it?
		if (mIsCardBeingDragged)
		{
			Pile* targetPile = getPileAtMousePosition();
			if (targetPile && targetPile->isValidMove(mDraggedCard))
			{
				// move the card to the target pile
				targetPile->push(mDraggedCard);
				mDraggedCardOriginalPile->pop();

				// flip the top card of the original pile
				if (mDraggedCardOriginalPile->peek())
				{	
					mDraggedCardOriginalPile->peek()->flip();
				}
			}
			else
			{
				// invalid move, snap card back to its original position
				resetDraggedCardPosition();
			}

			mIsCardBeingDragged = false;
		}
	}
}

// -----------------------------------------------------------------------------

void GameManager::update(sf::Time& pDeltaTime)
{
	const float deltaTimeSeconds = pDeltaTime.asSeconds();

	if (mIsCardBeingDragged && mDraggedCard)
	{
		// get the mouse position
		const sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindowRef));
		sf::Vector2f newPosition = mousePosition + mDraggedCardOffset;

		updateDraggedCardPosition(newPosition);
	}
}

// -----------------------------------------------------------------------------

void GameManager::render()
{
	mWindowRef.draw(mBlankSpace);

	// render the deck pile (stock and waste)
	mDeck.render(mWindowRef);

	// render the tableau piles
	for (uint32_t i = 0; i < mTableaus.size(); ++i)
	{
		mTableaus[i].render(mWindowRef);
	}

	// render the foundation piles
	for (uint32_t i = 0; i < mFoundations.size(); ++i)
	{
		mFoundations[i].render(mWindowRef);
	}

	if (mDraggedCard && mIsCardBeingDragged)
	{
		mDraggedCard->render(mWindowRef);
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

		mTableaus[i].setStartingPositions();
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

Card* GameManager::getCardAtMousePosition()
{
	// this will be the top card of any pile for the moment
	Card* card = nullptr;

	// get the mouse position
	const sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindowRef));

	// check the tableau piles
	for (uint32_t i = 0; i < mTableaus.size(); ++i)
	{
		if (mTableaus[i].isMouseOverTopCard(mousePosition))
		{
			card = mTableaus[i].peek();
			break;
		}
	}

	// check the foundation piles
	for (uint32_t i = 0; i < mFoundations.size(); ++i)
	{
		if (mFoundations[i].isMouseOverTopCard(mousePosition))
		{
			card = mFoundations[i].peek();
			break;
		}
	}

	// check the waste pile
	if (mDeck.isMouseOverWaste(sf::Mouse::getPosition(mWindowRef)))
	{
		card = mDeck.peekWaste();
	}

	return card;
}

// -----------------------------------------------------------------------------

Pile* GameManager::findPileContainingCard(Card* pSelectedCard)
{
// check the tableau piles
	for (uint32_t i = 0; i < mTableaus.size(); ++i)
	{
		if (mTableaus[i].isCardInPile(pSelectedCard))
		{
			return &mTableaus[i];
		}
	}

	// check the foundation piles
	for (uint32_t i = 0; i < mFoundations.size(); ++i)
	{
		if (mFoundations[i].isCardInPile(pSelectedCard))
		{
			return &mFoundations[i];
		}
	}

	// check the top card of the waste pile
	if (mDeck.peekWaste() == pSelectedCard)
	{
		return &mDeck.getWaste();
	}

	return nullptr;
}

// -----------------------------------------------------------------------------

Pile* GameManager::getPileAtMousePosition()
{
	// this will be the top card of any pile for the moment
	Pile* pile = nullptr;

	// get the mouse position
	const sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindowRef));

	// check the tableau piles
	for (uint32_t i = 0; i < mTableaus.size(); ++i)
	{
		if (mTableaus[i].isMouseOverTopCard(mousePosition))
		{
			pile = &mTableaus[i];
			break;
		}
	}

	// check the foundation piles
	for (uint32_t i = 0; i < mFoundations.size(); ++i)
	{
		if (mFoundations[i].isMouseOverTopCard(mousePosition))
		{
			pile = &mFoundations[i];
			break;
		}
	}

	return pile;
}

// -----------------------------------------------------------------------------

void GameManager::updateDraggedCardPosition(const sf::Vector2f& pNewPosition)
{
	// update the position of the card being dragged
	mDraggedCard->setPosition(pNewPosition);

	// update the position of the card being dragged children
	// to do
}

// -----------------------------------------------------------------------------

void GameManager::resetDraggedCardPosition()
{
	// reset the position of the card being dragged
	mDraggedCard->setPosition(mDraggedCardOriginalPosition);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------