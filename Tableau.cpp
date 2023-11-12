// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Tableau.h"

#include "Card.h"

#include <iostream>

// -----------------------------------------------------------------------------

Tableau::Tableau(const sf::Vector2f& pPosition)
	: Pile(pPosition)
{

}

// -----------------------------------------------------------------------------

Tableau::~Tableau()
{

}

// -----------------------------------------------------------------------------

bool Tableau::isValidMove(Card* pCard)
{
	// if the tableau is empty, only a king can be moved
	if (isEmpty())
	{
		if (pCard->getRank() == ECardRank::eKING)
		{	
			return true;
		}
		else
		{	
			return false;
		}
	}
	// if the pile is not empty, check if the card is the opposite color and one rank lower
	else
	{
		return isCardValid(pCard, peek());
	}
}

// -----------------------------------------------------------------------------

bool Tableau::isValidMove(std::vector<Card*>& pCards)
{
	// if the tableau is empty, only a king can be moved
	if (isEmpty())
	{
		if (pCards[0]->getRank() == ECardRank::eKING)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	// if the pile is not empty, check the pile of cards in the vector is in
	// correct order and the first card is the opposite color and one rank lower
	else
	{
		if (pCards.size() < 0 || pCards.size() > 13)
		{
			return false;
		}

		if (!areCardsValid(pCards))
		{
			return false;
		}
	}

	return true;
}

// -----------------------------------------------------------------------------

void Tableau::printToConsole()
{
	std::cout << "Tableau: ";
	Pile::printToConsole();
}

// -----------------------------------------------------------------------------

void Tableau::render(sf::RenderWindow& pWindow)
{
	if (!isEmpty())
	{
		// render the top card
		peek()->render(pWindow);

		// render the rest of the cards
		//for (int i = 1; i < mCards.size(); ++i)
		//{
			//mCards[i]->render(pWindow);
		//}
	}
}

// -----------------------------------------------------------------------------

bool Tableau::isCardValid(Card* pCard, Card* pCardAbove)
{
	const bool isOppositeColor = pCard->isRed() != pCardAbove->isRed();
	const bool isOneRankLower = pCard->getRank() == pCardAbove->getRank() - 1;

	if (isOppositeColor && isOneRankLower)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// -----------------------------------------------------------------------------

bool Tableau::areCardsValid(std::vector<Card*>& pCards)
{
	// check the top card
	if (!isCardValid(pCards[0], peek()))
	{
		return false;
	}

	for (int i = 1; i < pCards.size(); ++i)
	{
		if (!isCardValid(pCards[i], pCards[i - 1]))
		{
			return false;
		}
	}

	return true;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

