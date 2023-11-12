// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Pile.h"

#include <algorithm>
#include <iostream>
#include <random>

// -----------------------------------------------------------------------------

Pile::Pile(const sf::Vector2f& pPosition)
	: mPosition(pPosition)
{

}

// -----------------------------------------------------------------------------

Pile::~Pile()
{
	for (Card* card : mCards)
	{
		if (card)
		{
			delete card;
			card = nullptr;
		}
	}
}

// -----------------------------------------------------------------------------

void Pile::push(Card* pCard)
{
	pCard->getSprite().setPosition(mPosition);
	mCards.push_back(pCard);
}

// -----------------------------------------------------------------------------

Card* Pile::pop()
{
	Card* card = mCards.back();
	mCards.pop_back();
	return card;
}

// -----------------------------------------------------------------------------

Card* Pile::peek()
{
	return mCards.back();
}

// -----------------------------------------------------------------------------

void Pile::shuffle()
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(mCards.begin(), mCards.end(), g);
}

// -----------------------------------------------------------------------------

void Pile::printToConsole()
{
	for (Card* card : mCards)
	{
		card->printToConsole();
		std::cout << ' ';
	}
	std::cout << '\n';
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------