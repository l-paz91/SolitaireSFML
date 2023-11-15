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
	mBlankSpace.setFillColor(sf::Color(27, 18, 18, 100));
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
		if (!mIsCardBeingDragged)
		{
			std::vector<Card*> selectedCards = getCardsAtMousePosition(mousePosition);
			if (selectedCards.size() > 0)
			{
				mIsCardBeingDragged = true;
				mDraggedCardOriginalPile = findPileContainingCard(selectedCards[0]);

				// are we dragging single or multiple cards?
				if (selectedCards.size() == 1)
				{
					// start dragging the card
					mDraggedCard = selectedCards[0];
					mDraggedCardOriginalPosition = mDraggedCard->getSprite().getPosition();
					mDraggedCardOffset = mDraggedCardOriginalPosition - static_cast<sf::Vector2f>(mousePosition);
				}
				else
				{
					mDraggedCards = selectedCards;
					setDraggedCardsOriginalPositions();
				}
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
			if (mDraggedCard)
			{
				Pile* targetPile = getPileAtMousePosition();
				if (targetPile && targetPile->isValidMove(mDraggedCard))
				{
					// move the card to the target pile
					targetPile->push(mDraggedCard);
					mDraggedCardOriginalPile->pop();

					// flip the top card of the original pile
					if (Card* peekedCard = mDraggedCardOriginalPile->peek())
					{	
						if (!peekedCard->isFaceUp())
						{
							peekedCard->flip();
						}
					}
				}
				else
				{
					// invalid move, snap card back to its original position
					resetDraggedCardPosition();
				}

				mDraggedCard = nullptr;
			}
			else
			{
				resetDraggedCardsPosition();
				mDraggedCards.clear();
				mDraggedCardsOriginalPositions.clear();
			}

			mIsCardBeingDragged = false;
		}
	}
}

// -----------------------------------------------------------------------------

void GameManager::update(sf::Time& pDeltaTime)
{
	const float deltaTimeSeconds = pDeltaTime.asSeconds();

	if (mIsCardBeingDragged)
	{
		// get the mouse position
		const sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindowRef));
		sf::Vector2f newPosition = mousePosition + mDraggedCardOffset;

		if (mDraggedCard)
		{
			sf::Vector2f newPosition = mousePosition + mDraggedCardOffset;
			updateDraggedCardPosition(newPosition);
		}
		else
		{
			const float yOffset = 30.f;
			// we're dragging multiple cards
			for (uint32_t i = 0; i < mDraggedCards.size(); ++i)
			{
				sf::Vector2f newPosition = mousePosition + mDraggedCardOffset;
				newPosition.y += yOffset * i;
				mDraggedCards[i]->setPosition(newPosition);
			}
		}
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

	if (mIsCardBeingDragged)
	{
		if (mDraggedCard)
		{
			mDraggedCard->render(mWindowRef);
		}
		else
		{
			for (Card* card : mDraggedCards)
			{
				card->render(mWindowRef);
			}
		}
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

std::vector<Card*> GameManager::getCardsAtMousePosition(const sf::Vector2i& pMousePosition)
{
	Card* card = nullptr;
	std::vector<Card*> cards;

	// get the mouse position
	const sf::Vector2f mousePosition = static_cast<sf::Vector2f>(pMousePosition);

	// check the tableau piles
	for (uint32_t i = 0; i < mTableaus.size(); ++i)
	{
		if (mTableaus[i].isMouseOverCard(mousePosition, card))
		{
			if (card)
			{
				// is it a valid card to be dragged?
				if (card->isFaceUp())
				{
					mDraggedCardOffset = card->getSprite().getPosition() - static_cast<sf::Vector2f>(mousePosition);

					// check if it's a sequence, if it is, it will populate the cards
					if (!mTableaus[i].isValidSequence(card, cards))
					{
						cards.push_back(card);
						return cards;
					}
				}
			}

			return cards;
		}
	}

	// check the foundation piles
	for (uint32_t i = 0; i < mFoundations.size(); ++i)
	{
		if (mFoundations[i].isMouseOverTopCard(mousePosition))
		{
			card = mFoundations[i].peek();
			cards.push_back(card);
			return cards;
		}
	}

	// check the waste pile
	if (mDeck.isMouseOverWaste(pMousePosition))
	{
		card = mDeck.peekWaste();
		cards.push_back(card);
	}

	return cards;
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
		// we don't want to check the original pile (which our card is currently at the mouse position of)
		if (&mTableaus[i] != mDraggedCardOriginalPile)
		{
			if (mTableaus[i].isMouseOverTopCard(mousePosition))
			{
				pile = &mTableaus[i];
				return pile;
			}
		}
	}

	// check the foundation piles
	for (uint32_t i = 0; i < mFoundations.size(); ++i)
	{
		if (mFoundations[i].isMouseOverTopCard(mousePosition))
		{
			pile = &mFoundations[i];
			return pile;
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

void GameManager::resetDraggedCardsPosition()
{
	for(uint32_t i = 0; i < mDraggedCards.size(); ++i)
	{
		mDraggedCards[i]->setPosition(mDraggedCardsOriginalPositions[i]);
	}
}

// -----------------------------------------------------------------------------

void GameManager::setDraggedCardsOriginalPositions()
{
	for (Card* card : mDraggedCards)
	{
		mDraggedCardsOriginalPositions.push_back(card->getSprite().getPosition());
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------