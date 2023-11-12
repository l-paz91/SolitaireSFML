// -----------------------------------------------------------------------------
#ifndef Pile_H
#define Pile_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Card.h"

#include <vector>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

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
	Pile(const sf::Vector2f& pPosition);
	~Pile();

	// add a card to the top of the pile
	void push(Card* pCard);

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

	void setPosition(const sf::Vector2f& pPosition) { mPosition = pPosition; }
	const sf::Vector2f& getPosition() const { return mPosition; }

	// debug print to console
	void printToConsole();

private:
	std::vector<Card*> mCards;
	sf::Vector2f mPosition;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Pile_H