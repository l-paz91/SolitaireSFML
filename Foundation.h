// -----------------------------------------------------------------------------
#ifndef Foundation_H
#define Foundation_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Pile.h"

#include <SFML/Graphics/RectangleShape.hpp>

// -----------------------------------------------------------------------------

/*
	// ---- Foundation Class ----//
		
	A foundation is a collection of cards, it has to be in order from Ace to King
	of the same suit. There are 4 foundations in a game of solitaire.

	Foundation piles start empty and cards are added to them in order. The first
	card added to a foundation is an ace, the second card added is a 2, and so on
	until the king is added.

	When a foundation is full, it cannot be added to. When all 4 foundations are
	full, the game is won.

	Cards can be moved from the top of a foundation to a tableau pile if the card
	is the opposite color and one rank lower than the card it is being moved onto.

*/

// -----------------------------------------------------------------------------

class Foundation : public Pile
{
public:
	// Foundation constructor
	Foundation(const sf::Vector2f& pPosition);

	// Foundation destructor
	~Foundation();

	// checks if a card can be moved to the foundation
	virtual bool isValidMove(Card* pCard) override;

	// debug print to console
	void printToConsole();

	// core functions
	void render(sf::RenderWindow& pWindow);

	void setPosition(const sf::Vector2f& pPosition) { mBlankSpace.setPosition(pPosition); }

private:
	sf::RectangleShape mBlankSpace;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Foundation_H