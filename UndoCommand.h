// -----------------------------------------------------------------------------
#ifndef UndoCommand_H
#define UndoCommand_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Card.h"
#include "Pile.h"
#include "ScoringSystem.h"

#include <iostream>

// -----------------------------------------------------------------------------

enum class EMoveType
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
		: mMoveType(EMoveType::eDEFAULT)
		, mCards()
		, mFromPile(nullptr)
		, mToPile(nullptr)
		, mMoveScore(0)
		, mOriginalFaceUpState(false)
	{}

	Undo(EMoveType pMoveType, const std::vector<Card*>& pCard, Pile* pFromPile, EScoringSystem pScore, Pile* pToPile)
		: mMoveType(pMoveType)
		, mCards(pCard)
		, mFromPile(pFromPile)
		, mToPile(pToPile)
		, mMoveScore(pScore)
		, mOriginalFaceUpState(false)
	{
	}

	Undo(EMoveType pMoveType, Card* pCard, Pile* pFromPile, EScoringSystem pScore, Pile* pToPile)
		: mMoveType(pMoveType)
		, mCards()
		, mFromPile(pFromPile)
		, mToPile(pToPile)
		, mMoveScore(pScore)
		, mOriginalFaceUpState(false)
	{
		mCards.push_back(pCard);
	}

	~Undo() {}

	void debugPrint()
	{
		std::cout << "Undo: || ";
		std::cout << "MoveType: " << static_cast<int>(mMoveType);
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
	int mMoveScore;				// the score of the move
	bool mOriginalFaceUpState;	// the original face up state of the card below it
};


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !UndoCommand_H