// -----------------------------------------------------------------------------
#ifndef UndoCommand_H
#define UndoCommand_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Card.h"
#include "Pile.h"
#include <iostream>

// -----------------------------------------------------------------------------

enum EMoveType
{
	eDRAW,			// we've drawn a card from the deck
	eRESET,			// the card has snapped back to its original position
	eTRANSFER,		// we've moved a card from one pile to another
	eFLIP,			// we've flipped a card over
	eDEFAULT		// default value
};

// -----------------------------------------------------------------------------

struct Undo
{
	Undo()
		: mMoveType(eDEFAULT)
		, mCards()
		, mFromPile(nullptr)
		, mToPile(nullptr)
		, mOriginalFaceUpState(false)
	{}

	Undo(EMoveType pMoveType, const std::vector<Card*>& pCard, Pile* pFromPile, Pile* pToPile)
		: mMoveType(pMoveType)
		, mCards(pCard)
		, mFromPile(pFromPile)
		, mToPile(pToPile)
		, mOriginalFaceUpState(false)
	{
	}

	Undo(EMoveType pMoveType, Card* pCard, Pile* pFromPile, Pile* pToPile)
		: mMoveType(pMoveType)
		, mCards()
		, mFromPile(pFromPile)
		, mToPile(pToPile)
		, mOriginalFaceUpState(false)
	{
		mCards.push_back(pCard);
	}

	~Undo() {}

	void debugPrint()
	{
		std::cout << "Undo: || ";
		std::cout << "MoveType: " << mMoveType;
		std::cout << " || Cards: ";
		for (Card* card : mCards)
		{
			if (card)
			{
				card->printToConsole();
				std::cout << ", ";
			}
		}
		std::cout << " || FromPile: "; mFromPile->printName();
		std::cout << " || ToPile: "; mToPile->printName();
	}

	EMoveType mMoveType;
	std::vector<Card*> mCards;	// the card(s) that moved
	Pile* mFromPile;			// the pile the card was moved from
	Pile* mToPile;				// the pile the card was moved to
	bool mOriginalFaceUpState;	// the original face up state of the card below it
};


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !UndoCommand_H