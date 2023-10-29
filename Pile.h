// -----------------------------------------------------------------------------
#ifndef Pile_H
#define Pile_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Card.h"

#include <vector>

// -----------------------------------------------------------------------------

/*
	// ---- Pile Class ----//
	
	A pile is a collection of cards, it can be a deck, a tableau, a foundation 
	or a waste.
*/

// -----------------------------------------------------------------------------

class Pile
{
public:
	Pile();
	~Pile();

	// add a card to the top of the pile
	void push(const Card& pCard);

	// removes the top card from the pile
	Card* pop();

	// view the top card without removing it
	Card* peek();

	// shuffle the pile
	void shuffle();

	// check if pile is empty
	bool isEmpty() { return mCards.empty(); }

	// get cards
	std::vector<Card*>& getCards() { return mCards; }

private:
	std::vector<Card*> mCards;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Pile_H