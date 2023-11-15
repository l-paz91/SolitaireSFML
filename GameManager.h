// -----------------------------------------------------------------------------
#ifndef GameManager_H
#define GameManager_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Card.h"
#include "Deck.h"
#include "Foundation.h"
#include "Tableau.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

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

	void beginGame();

private:
	Card* getCardAtMousePosition();

	Pile* findPileContainingCard(Card* pSelectedCard);
	Pile* getPileAtMousePosition();

	void updateDraggedCardPosition(const sf::Vector2f& pNewPosition);
	void resetDraggedCardPosition();
	void handleCardDrop();

	sf::Sprite mCardBackSprite;
	sf::RectangleShape mBlankSpace;
	sf::RenderWindow& mWindowRef;

	Deck mDeck;
	std::vector<Tableau> mTableaus;
	std::vector<Foundation> mFoundations;

	Card* mDraggedCard;
	Pile* mDraggedCardOriginalPile;
	sf::Vector2f mDraggedCardOriginalPosition;
	sf::Vector2f mDraggedCardOffset;

	bool mIsCardBeingDragged;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !GameManager_H