// -----------------------------------------------------------------------------
#ifndef GameManager_H
#define GameManager_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Card.h"
#include "Deck.h"
#include "Foundation.h"
#include "Tableau.h"
#include "UndoCommand.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <vector>

// -----------------------------------------------------------------------------

enum EGameState
{
	ePLAYING,
	eWON,
	eEND
};

// -----------------------------------------------------------------------------

struct AnimatedCard
{
	Card* mCard;
	sf::Vector2f mVelocity;
	int mFoundationPileIndex;
	int mFoundationCardIndex;
	float mAnimationTime;
	float mGravity;
	float mEnergyLoss;
	float mInitialVerticalVelocity;

	void reset(float pXVel, float pYVel)
	{
		mVelocity = sf::Vector2f(pXVel, pYVel);
		mAnimationTime = 0.f;
		mInitialVerticalVelocity = pYVel;
	}
};

// -----------------------------------------------------------------------------

class GameManager
{
public:
	GameManager(sf::RenderWindow& pWindow);
	~GameManager();

	void init();

	void processEvents(const sf::Event& pEvent);
	void update(sf::Time& pDeltaTime);
	void render();
	void renderWinAnimation(sf::RenderTexture& mRenderTexture);

	void beginGame();

	EGameState getGameState() { return mGameState; }

private:
	void debugWinGame();

	void winAnimation(sf::Time& pDeltaTime);

	// handle mouse events
	void handleLeftMouseButtonPress(const sf::Vector2i& pMousePosition);
	void handleLeftMouseButtonRelease(const sf::Vector2i& pMousePosition);
	void handleRightMouseButtonRelease(const sf::Vector2i& pMousePosition);

	float getCardXVelocity();
	float getCardYVelocity();

	void debugPrintMoveHistory();
	void undoMove();

	std::vector<Card*> getCardsAtMousePosition(const sf::Vector2i& pMousePosition);

	Pile* findPileContainingCard(Card* pSelectedCard);
	Pile* getPileAtMousePosition();
	Pile* getCorrectFoundationPile(Card* pSelectedCard);

	void updateDraggedCardPosition(const sf::Vector2f& pNewPosition);
	void resetDraggedCardPosition();
	void resetDraggedCardsPosition();
	void setDraggedCardsOriginalPositions();

	bool gameWon();

	sf::Sprite mCardBackSprite;
	sf::RectangleShape mBlankSpace;
	sf::RenderWindow& mWindowRef;

	Deck mDeck;
	std::vector<Tableau> mTableaus;
	std::vector<Foundation> mFoundations;

	std::vector<Card*> mDraggedCards;
	std::vector<sf::Vector2f> mDraggedCardsOriginalPositions;

	Card* mDraggedCard;
	Pile* mDraggedCardOriginalPile;
	sf::Vector2f mDraggedCardOriginalPosition;
	sf::Vector2f mDraggedCardOffset;

	std::vector<Undo> mMoveHistory;

	AnimatedCard mAnimatedCard;
	bool mIsCardBeingDragged;
	EGameState mGameState;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !GameManager_H