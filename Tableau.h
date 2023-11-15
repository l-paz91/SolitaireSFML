// -----------------------------------------------------------------------------
#ifndef Tableau_H
#define Tableau_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Pile.h"

#include <SFML/System/Vector2.hpp>

// -----------------------------------------------------------------------------

class Card;

// -----------------------------------------------------------------------------

/*
	// ---- Tableau Class ----//

	A tableau is a pile of cards that can be built down by alternating colors.
	There are 7 tableaus in a game of solitaire. 
	
	The first tableau has 1 card, the second has 2 cards, the third has 3 cards
	and so on. The top card of a must be face up, the rest are face down. 
	
	A card can be moved from the top of a tableau if it is face up and if it is
	of the opposite color and one rank lower than the card it is being moved onto.

	Tableaus are built down by alternating colors. For example, a black 7 can be
	moved onto a red 8, a red 6 can be moved onto a black 7, and so on.

	A card can be moved from the top of a tableau to an empty tableau if it is a
	king.

	An ace can be moved from the top of a tableau to a foundation.
*/

// -----------------------------------------------------------------------------

class Tableau : public Pile
{
public:
	// TableauPile constructor
	Tableau(const sf::Vector2f& pPosition);

	// TableauPile destructor
	~Tableau();

	// checks if a card can be moved to the tableau

	// Begin Pile Interface
	virtual bool isValidMove(Card* pCard) override;
	virtual void push(Card* pCard) override;
	virtual bool isMouseOverTopCard(const sf::Vector2f& pMousePos);
	// ~Pile Interface

	bool isValidMove(std::vector<Card*>& pCards);

	// debug print to console
	void printToConsole();

	// core functions
	void render(sf::RenderWindow& pWindow);
	
	void setStartingPositions();

private:
	bool isCardValid(Card* pCard, Card* pCardAbove);
	bool areCardsValid(std::vector<Card*>& pCards);

	sf::Sprite mBlankSpace;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Tableau_H