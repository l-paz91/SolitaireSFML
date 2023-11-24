// -----------------------------------------------------------------------------
#ifndef Pile_H
#define Pile_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Card.h"

#include <vector>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>

// -----------------------------------------------------------------------------

/*
	// ---- Pile Class ----//
	
	A pile is a collection of cards, it can be a deck, a tableau, a foundation 
	or a waste.
*/

// -----------------------------------------------------------------------------

enum class EPileType
{
	eDEFAULT,
	eTABLEAU,
	eFOUNDATION,
	eWASTE,
	eSTOCK
};

// -----------------------------------------------------------------------------

class Pile
{
public:
	Pile(const sf::Vector2f& pPosition);
	~Pile();

	// add a card to the top of the pile
	virtual void push(Card* pCard);

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

	// is mouse over top card in pile
	virtual bool isMouseOverTopCard(const sf::Vector2f& pMousePos);

	// is mouse over card in pile
	virtual bool isMouseOverCard(const sf::Vector2f& pMousePos, Card*& pOutSelectedCard);

	// is card in pile
	bool isCardInPile(Card* pCard);

	virtual bool isValidMove(Card* pCard) { return false; };
	virtual bool isValidMove(std::vector<Card*>& pCards);

	virtual void printName() { std::cout << "Pile" << std::endl;}
	virtual int getID() { return -1; }

	void setPileType(EPileType pType) { mPileType = pType; }
	EPileType getPileType() { return mPileType; }

private:
	std::vector<Card*> mCards;
	sf::Vector2f mPosition;

	EPileType mPileType;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Pile_H