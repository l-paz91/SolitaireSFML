// -----------------------------------------------------------------------------
#ifndef Deck_H
#define Deck_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Pile.h"

// -----------------------------------------------------------------------------

/*
	// ---- Deck Class ----//

	A deck is a collection of cards. Here it represents the stock pile and the
	waste pile.
*/

// -----------------------------------------------------------------------------

class Deck
{
public:
	// Deck constructor
	Deck();

	// Deck destructor
	~Deck();

	// core functions
	void render(sf::RenderWindow& pWindow);

	// prints the deck of cards to console window
	void printStockToConsole();
	void printWasteToConsole();

	// moves the top card(s) from the stock to the waste
	void draw();

	// moves cards from the waste back to the stock
	void reset();

	// check if we're hovering over the stock or waste
	bool isMouseOverStock(const sf::Vector2i& pMousePos);
	bool isMouseOverWaste(const sf::Vector2i& pMousePos);

	// is the stock empty?
	bool isStockEmpty() { return mStock.isEmpty(); }

	// peek the top card of the stock
	Card* peekStock() { return mStock.peek(); }
	void popStock() { mStock.pop(); }

	// peek the top card of the waste
	Card* peekWaste() { return mWaste.peek(); }

	Pile& getStock() { return mStock; }
	Pile& getWaste() { return mWaste; }

private:
	Pile mStock;
	Pile mWaste;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Deck_H