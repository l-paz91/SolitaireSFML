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
	std::vector<Card*> getCardsAtMousePosition(const sf::Vector2i& pMousePosition);

	Pile* findPileContainingCard(Card* pSelectedCard);
	Pile* getPileAtMousePosition();

	void updateDraggedCardPosition(const sf::Vector2f& pNewPosition);
	void resetDraggedCardPosition();
	void resetDraggedCardsPosition();
	void setDraggedCardsOriginalPositions();
	void setDraggedCardsMouseOffsets();

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

	bool mIsCardBeingDragged;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !GameManager_H