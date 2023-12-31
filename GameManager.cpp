// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "GameManager.h"
#include "GameFacilities.h"
#include "TextureManager.h"
#include "SoundManager.h"

#include <SFML/Window/Event.hpp>

// -----------------------------------------------------------------------------

namespace GameManagerPrivate
{
	const float TIME_PER_CARD = 5.0f;

	const std::string cardFlipSFX = "CardFlip";
	const std::string cardPickUpSFX = "CardPickUp";
	const std::string cardPlaceSFX = "CardPlace";

}

// -----------------------------------------------------------------------------

GameManager::GameManager(sf::RenderWindow& pWindow)
	: mWindowRef(pWindow)
{
	// set up card back sprite
	mCardBackSprite.setTexture(TextureManager::getTexture("Graphics/CardSpritesheet.png"));
	mCardBackSprite.setTextureRect(sf::IntRect(0, 680, 118, 170));
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

	mGameState = EGameState::ePLAYING;

	mClickCountLMB = 0;
	mDoubleClickTimer = 0.2f;

	// load background music
	SoundManager::loadMusic("Cocktail-Hour-Aaron-Kenny", "Sounds/Cocktail-Hour-Aaron-Kenny.ogg");

	// load sound effects
	SoundManager::loadSound(GameManagerPrivate::cardFlipSFX, "Sounds/CardFlip.wav");
	SoundManager::loadSound(GameManagerPrivate::cardPlaceSFX, "Sounds/CardPlace.wav");
	SoundManager::loadSound(GameManagerPrivate::cardPickUpSFX, "Sounds/CardPick.wav");
}

// -----------------------------------------------------------------------------

GameManager::~GameManager()
{

}

// -----------------------------------------------------------------------------

void GameManager::init()
{
	beginGame();
	//debugWinGame();
}

// -----------------------------------------------------------------------------

void GameManager::processEvents(const sf::Event& pEvent)
{
	using namespace sf;
	const Vector2i mousePosition = Mouse::getPosition(mWindowRef);

	// process card events

	// ctrl+z pressed
	if (pEvent.type == Event::KeyPressed && pEvent.key.code == Keyboard::Z && Keyboard::isKeyPressed(Keyboard::LControl))
	{
		undoMove();
	}

	// LMB pressed
	if (pEvent.type == Event::MouseButtonPressed && pEvent.mouseButton.button == Mouse::Left)
	{
		handleLeftMouseButtonPress(mousePosition);
	}

	// LMB released
	if (pEvent.type == Event::MouseButtonReleased && pEvent.mouseButton.button == Mouse::Left)
	{
		handleLeftMouseButtonRelease(mousePosition);

		float timeSinceLastClick = mDoubleClickClock.getElapsedTime().asSeconds();
		if (timeSinceLastClick < mDoubleClickTimer)
		{
			++mClickCountLMB;
			if (mClickCountLMB == 2)
			{
				handleDoubleClick(mousePosition);
				mClickCountLMB = 0;
			}
		}
		else
		{
			mClickCountLMB = 1;
			mDoubleClickClock.restart();
		}
	}

	// RMB released
	if (pEvent.type == Event::MouseButtonReleased && pEvent.mouseButton.button == Mouse::Right)
	{
		handleRightMouseButtonRelease(mousePosition);
	}
}

// -----------------------------------------------------------------------------

void GameManager::update(sf::Time& pDeltaTime)
{
	const float deltaTimeSeconds = pDeltaTime.asSeconds();

	if (mGameState == ePLAYING)
	{
		// update timer on status bar
		mStatusBar.update(deltaTimeSeconds);

		if (mIsCardBeingDragged)
		{
			// get the mouse position
			const sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindowRef));
			sf::Vector2f newPosition = mousePosition + mDraggedCardOffset;

			if (mDraggedCards.size())
			{
				const float yOffset = 30.f;

				// we're dragging multiple cards
				for (uint32_t i = 0; i < mDraggedCards.size(); ++i)
				{
					sf::Vector2f newPosition = mousePosition + mDraggedCardOffset;
					newPosition.y += yOffset * i;
					mDraggedCards[i]->setPosition(newPosition);
				}

				// update the position of the outlines
				for (uint32_t i = 0; i < mDraggedCards.size(); ++i)
				{
					mDraggedCards[i]->setOutlinePosition();
				}
			}
		}

		// check if the game has been won
		if (gameWon())
		{
			mGameState = EGameState::eWON;
			mAnimatedCard.mCard = mFoundations[0].peek();

			float xVel = getCardXVelocity();
			float yVel = getCardYVelocity();

			mAnimatedCard.mVelocity = sf::Vector2f(xVel, yVel);
			mAnimatedCard.mFoundationPileIndex = 0;
			mAnimatedCard.mFoundationCardIndex = 12;
			mAnimatedCard.mAnimationTime = 0.f;
			mAnimatedCard.mGravity = 2.f;
			mAnimatedCard.mEnergyLoss = 0.8f;
			mAnimatedCard.mInitialVerticalVelocity = yVel;

			mWindowRef.setFramerateLimit(30);
		}
	}
	else if (mGameState == eWON)
	{
		winAnimation(pDeltaTime);
	}
}

// -----------------------------------------------------------------------------

void GameManager::render()
{
	mWindowRef.draw(mBlankSpace);

	// render the deck pile (stock and waste)
	mDeck.render(mWindowRef);

	if (mGameState == EGameState::eWON)
	{
		mAnimatedCard.mCard->render(mWindowRef);
	}

	// render the foundation piles
	for (uint32_t i = 0; i < mFoundations.size(); ++i)
	{
		mFoundations[i].render(mWindowRef);
	}

	if (mGameState == ePLAYING)
	{
		// render the tableau piles
		for (uint32_t i = 0; i < mTableaus.size(); ++i)
		{
			mTableaus[i].render(mWindowRef);
		}

		if (mIsCardBeingDragged)
		{
			if (mDraggedCards.size())
			{
				for (Card* card : mDraggedCards)
				{
					card->render(mWindowRef);
				}
			}
		}
	}

	// render the status bar
	mStatusBar.render(mWindowRef);
}

// -----------------------------------------------------------------------------

void GameManager::renderWinAnimation(sf::RenderTexture& mRenderTexture)
{
	mRenderTexture.draw(mAnimatedCard.mCard->getSprite());
}

// -----------------------------------------------------------------------------

void GameManager::beginGame()
{
	if (mGameState == ePLAYING)
	{
		// start background music
		SoundManager::playMusic("Cocktail-Hour-Aaron-Kenny");

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
		//for (int i = 0; i < 7; ++i)
		//{
		//	mTableaus[i].printToConsole();
		//}
	}
}

// -----------------------------------------------------------------------------

void GameManager::debugWinGame()
{
	// deal the cards out so that one move results in a win
	if (mGameState == ePLAYING)
	{
		// deal cards to tableau piles from the deck
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 13; ++j)
			{
				if (i == 3 && j == 12)
				{
					break;
				}
				// deal cards from the deck to the foundation piles
				Card* card = mDeck.peekStock();
				card->flip();
				mFoundations[i].push(mDeck.peekStock());
				mDeck.popStock();
			}
		}
	}
}

// -----------------------------------------------------------------------------

void GameManager::winAnimation(sf::Time& pDeltaTime)
{
	const float deltaTimeSeconds = pDeltaTime.asSeconds();

	// play bouncing card animation with foundation piles
	mAnimatedCard.mAnimationTime += deltaTimeSeconds;

	// check if it's time to go to the next card
	sf::Vector2f cardPos = mAnimatedCard.mCard->getSprite().getPosition();
	sf::FloatRect cardRect = mAnimatedCard.mCard->getSprite().getGlobalBounds();

	const int windowMaxX = mWindowRef.getSize().x;

	if (cardPos.x > windowMaxX || cardPos.x < 0-cardRect.width)
	{
		float xVel = getCardXVelocity();
		float yVel = getCardYVelocity();
		mAnimatedCard.reset(xVel, yVel);

		++mAnimatedCard.mFoundationPileIndex;
		if (mAnimatedCard.mFoundationPileIndex >= 4)
		{
			mAnimatedCard.mFoundationPileIndex = 0;
			--mAnimatedCard.mFoundationCardIndex;

			if (mAnimatedCard.mFoundationCardIndex < 0)
			{
				mGameState = EGameState::eEND;
			}
		}

		if (mAnimatedCard.mFoundationCardIndex)
		{
			mAnimatedCard.mCard = mFoundations[mAnimatedCard.mFoundationPileIndex].getCards()[mAnimatedCard.mFoundationCardIndex];
		}
		else
		{
			mGameState = EGameState::eEND;
		}
	}

	mAnimatedCard.mVelocity.y += mAnimatedCard.mGravity;
	mAnimatedCard.mCard->getSprite().move(mAnimatedCard.mVelocity);

	// Bounce if hitting the bottom of the window
	cardPos = mAnimatedCard.mCard->getSprite().getPosition();
	cardRect = mAnimatedCard.mCard->getSprite().getGlobalBounds();

	if (cardPos.y + cardRect.height >= mWindowRef.getSize().y) 
	{
		mAnimatedCard.mCard->getSprite().setPosition(cardPos.x, mWindowRef.getSize().y - cardRect.height);
		mAnimatedCard.mVelocity.y *= -mAnimatedCard.mEnergyLoss; // Invert and reduce vertical velocity
		mAnimatedCard.mVelocity.x *= 1.2f; // increase horizontal velocity
	}
}

// -----------------------------------------------------------------------------

void GameManager::handleLeftMouseButtonPress(const sf::Vector2i& pMousePosition)
{
	if (!mIsCardBeingDragged)
	{
		std::vector<Card*> selectedCards = getCardsAtMousePosition(pMousePosition);
		if (selectedCards.size() > 0)
		{
			mIsCardBeingDragged = true;
			mDraggedCardOriginalPile = findPileContainingCard(selectedCards[0]);

			SoundManager::playSound(GameManagerPrivate::cardPickUpSFX);

			mDraggedCards = selectedCards;
			setDraggedCardsOriginalPositions();

			// toggle selected on all cards
			for (Card* card : mDraggedCards)
			{
				card->toggleSelected();
			}
		}
	}
}

// -----------------------------------------------------------------------------

void GameManager::handleLeftMouseButtonRelease(const sf::Vector2i& pMousePosition)
{
	// is the stock empty?
	if (mBlankSpace.getGlobalBounds().contains(static_cast<float>(pMousePosition.x), static_cast<float>(pMousePosition.y))
		&& mDeck.isStockEmpty())
	{
		mDeck.reset();
		mStatusBar.setScore(EScoringSystem::eREFLIP_WASTE);
		mStatusBar.incrementMoves();

		// play sound effect
		SoundManager::playSound(GameManagerPrivate::cardFlipSFX);
	}

	// are we hovering over stock?
	if (mDeck.isMouseOverStock(pMousePosition) && !mIsCardBeingDragged)
	{
		mDeck.draw();
		mStatusBar.incrementMoves();
		SoundManager::playSound(GameManagerPrivate::cardPickUpSFX);

		// create move history for undo command
		Undo move(EMoveType::eDRAW, mDeck.peekWaste(), &mDeck.getStock(), EScoringSystem::eDEFAULT, &mDeck.getWaste());
		mMoveHistory.push_back(move);
		debugPrintMoveHistory();
	}

	// are dragging a card and releasing it?
	if (mIsCardBeingDragged)
	{
		Pile* targetPile = getPileAtMousePosition();
		if (targetPile && targetPile->isValidMove(mDraggedCards))
		{
			// move the cards to the target pile in the correct order
			for (Card* card : mDraggedCards)
			{
				targetPile->push(card);
				mDraggedCardOriginalPile->pop();
			}

			SoundManager::playSound(GameManagerPrivate::cardPlaceSFX);

			// determine the score
			EPileType fromPileType = mDraggedCardOriginalPile->getPileType();
			EPileType toPileType = targetPile->getPileType();
			EScoringSystem scoreType = determineScore(fromPileType, toPileType);

			// create move history for undo command
			Undo move(EMoveType::eTRANSFER, mDraggedCards, mDraggedCardOriginalPile, scoreType, targetPile);

			// flip the top card of the original pile
			if (Card* peekedCard = mDraggedCardOriginalPile->peek())
			{
				if (!peekedCard->isFaceUp())
				{
					peekedCard->flip();
					SoundManager::playSound(GameManagerPrivate::cardFlipSFX);

					if (mDraggedCardOriginalPile->getPileType() == EPileType::eTABLEAU)
					{
						mStatusBar.setScore(EScoringSystem::eFLIP_TABLEAU_CARD);
						move.mMoveScore += EScoringSystem::eFLIP_TABLEAU_CARD;
					}
				}
				else
				{
					move.mOriginalFaceUpState = true;
				}
			}

			mStatusBar.incrementMoves();
			mMoveHistory.push_back(move);
			debugPrintMoveHistory();
		}
		else
		{
			resetDraggedCardsPosition();
		}

		// toggle selected on all cards
		for (Card* card : mDraggedCards)
		{
			card->toggleSelected();
		}

		mDraggedCards.clear();
		mDraggedCardsOriginalPositions.clear();

		mIsCardBeingDragged = false;
	}
}

// -----------------------------------------------------------------------------

void GameManager::handleRightMouseButtonRelease(const sf::Vector2i& pMousePosition)
{
	// on release, check if the mouse is over a single card
	// if it is, check if it's a valid move to the foundation pile
	sendCardToFoundationPile(pMousePosition);

	SoundManager::playSound(GameManagerPrivate::cardPlaceSFX);
}

// -----------------------------------------------------------------------------

void GameManager::handleDoubleClick(const sf::Vector2i& pMousePosition)
{
	sendCardToFoundationPile(pMousePosition);
}

// -----------------------------------------------------------------------------

void GameManager::sendCardToFoundationPile(const sf::Vector2i& pMousePosition)
{
	std::vector<Card*> selectedCards = getCardsAtMousePosition(pMousePosition);

	if (selectedCards.size() == 1)
	{
		mDraggedCardOriginalPile = findPileContainingCard(selectedCards[0]);

		if (Pile* targetPile = getCorrectFoundationPile(selectedCards[0]))
		{
			// is it a valid move to the foundation pile?
			if (targetPile->isValidMove(selectedCards[0]))
			{
				// move the card to the foundation pile
				targetPile->push(selectedCards[0]);
				mDraggedCardOriginalPile->pop();

				// determine the score
				EPileType fromPileType = mDraggedCardOriginalPile->getPileType();
				EPileType toPileType = targetPile->getPileType();
				EScoringSystem scoreType = determineScore(fromPileType, toPileType);

				// create move history for undo command
				Undo move(EMoveType::eTRANSFER, selectedCards, mDraggedCardOriginalPile, scoreType, targetPile);

				// flip the top card of the original pile
				if (Card* peekedCard = mDraggedCardOriginalPile->peek())
				{
					if (!peekedCard->isFaceUp())
					{
						peekedCard->flip();
						if (mDraggedCardOriginalPile->getPileType() == EPileType::eTABLEAU)
						{
							mStatusBar.setScore(EScoringSystem::eFLIP_TABLEAU_CARD);
							move.mMoveScore += EScoringSystem::eFLIP_TABLEAU_CARD;
						}
					}
					else
					{
						move.mOriginalFaceUpState = true;
					}
				}

				mStatusBar.incrementMoves();
				mMoveHistory.push_back(move);
				debugPrintMoveHistory();
			}
		}
	}
}

// -----------------------------------------------------------------------------

EScoringSystem GameManager::determineScore(EPileType pFromPile, EPileType pToPile)
{
	if (pFromPile == EPileType::eTABLEAU && pToPile == EPileType::eFOUNDATION)
	{
		mStatusBar.setScore(EScoringSystem::eTABLEAU_TO_FOUNDATION);
		return EScoringSystem::eTABLEAU_TO_FOUNDATION;
	}
	else if (pFromPile == EPileType::eFOUNDATION && pToPile == EPileType::eTABLEAU)
	{
		mStatusBar.setScore(EScoringSystem::eFOUNDATION_TO_TABLEAU);
		return EScoringSystem::eFOUNDATION_TO_TABLEAU;
	}
	else if (pFromPile == EPileType::eWASTE && pToPile == EPileType::eFOUNDATION)
	{
		mStatusBar.setScore(EScoringSystem::eWASTE_TO_FOUNDATION);
		return EScoringSystem::eWASTE_TO_FOUNDATION;
	}
	else if (pFromPile == EPileType::eWASTE && pToPile == EPileType::eTABLEAU)
	{
		mStatusBar.setScore(EScoringSystem::eWASTE_TO_TABLEAU);
		return EScoringSystem::eWASTE_TO_TABLEAU;
	}

	return EScoringSystem::eDEFAULT;
}

// -----------------------------------------------------------------------------

float GameManager::getCardXVelocity()
{
	int left = GameFacilities::randint(-12, -5);
	int right = GameFacilities::randint(5, 12);

	int random = GameFacilities::randint(0, 1);
	return static_cast<float>(random == 0 ? left : right);
}

// -----------------------------------------------------------------------------

float GameManager::getCardYVelocity()
{
	return static_cast<float>(GameFacilities::randint(-15, -7));
}

// -----------------------------------------------------------------------------

void GameManager::debugPrintMoveHistory()
{
	// print the last move added to the vector
	if (mMoveHistory.size() > 0)
	{
		mMoveHistory.back().debugPrint();
	}
}

// -----------------------------------------------------------------------------

void GameManager::undoMove()
{
	if (mMoveHistory.empty())
	{
		return;
	}

	Undo lastMove = mMoveHistory.back();
	mMoveHistory.pop_back();

	switch (lastMove.mMoveType)
	{
		case EMoveType::eDRAW:
		{
			// undo drawing a card
			lastMove.mCards.back()->flip();
			lastMove.mFromPile->push(lastMove.mCards.back());
			lastMove.mToPile->pop();
			mStatusBar.incrementMoves();
			break;
		}
		case EMoveType::eTRANSFER:
		{
			// flip the top card of the original pile only if it came from a tableau pile
			if (lastMove.mFromPile->getID() == 1)
			{
				if (Card* peekedCard = lastMove.mFromPile->peek())
				{
					if (!lastMove.mOriginalFaceUpState)
					{
						peekedCard->flip();
					}
				}
			}

			// undo transferring cards
			if (lastMove.mCards.size() == 1)
			{
				lastMove.mFromPile->push(lastMove.mCards.back());
				lastMove.mToPile->pop();
			}
			else
			{
				for (Card* card : lastMove.mCards)
				{
					lastMove.mFromPile->push(card);
					lastMove.mToPile->pop();
				}
			}

			// undo the score
			mStatusBar.decrementScore(lastMove.mMoveScore);
			mStatusBar.incrementMoves();

			break;
		}
		default:
			break;
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
			if (card = mFoundations[i].peek())
			{
				cards.push_back(card);
				mDraggedCardOffset = card->getSprite().getPosition() - static_cast<sf::Vector2f>(mousePosition);
				return cards;
			}
		}
	}

	// check the waste pile
	if (mDeck.isMouseOverWaste(pMousePosition))
	{
		if (card = mDeck.peekWaste())
		{
			cards.push_back(card);
			mDraggedCardOffset = card->getSprite().getPosition() - static_cast<sf::Vector2f>(mousePosition);
		}
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

Pile* GameManager::getCorrectFoundationPile(Card* pSelectedCard)
{
	if (pSelectedCard->getRank() == ECardRank::eACE)
	{
		// is it an ace? if so, return the first empty foundation pile
		for (Foundation& foundation : mFoundations)
		{
			if (foundation.isEmpty())
			{
				return &foundation;
			}
		}
	}

	ECardSuit selectedCardSuit = pSelectedCard->getSuit();

	for (Foundation& foundation : mFoundations)
	{
		if (foundation.getSuit() == selectedCardSuit)
		{
			return &foundation;
		}
	}

	return nullptr;
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

bool GameManager::gameWon()
{
	// if there are 13 cards in each of the 4 foundations, the game is won
	for (uint32_t i = 0; i < mFoundations.size(); ++i)
	{
		if (mFoundations[i].getCards().size() != 13)
		{
			return false;
		}
	}

	return true;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------