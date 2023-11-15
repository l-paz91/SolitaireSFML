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
	if (mCards.empty())
	{
		return nullptr;
	}

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

bool Pile::isMouseOverTopCard(const sf::Vector2f& pMousePos)
{
	if (mCards.empty())
	{
		return false;
	}

	return mCards.back()->getSprite().getGlobalBounds().contains(pMousePos);
}

// -----------------------------------------------------------------------------

bool Pile::isMouseOverCard(const sf::Vector2f& pMousePos, Card*& pOutSelectedCard)
{
	if (mCards.empty())
	{
		return false;
	}

	// Iterate in reverse order so that we're not returning cards that have other 
	// cards drawn on top of them
	for (auto it = mCards.rbegin(); it != mCards.rend(); ++it)
	{
		Card* card = *it;
		if (card->getSprite().getGlobalBounds().contains(pMousePos))
		{
			pOutSelectedCard = card;
			return true;
		}
	}

	return false;
}

// -----------------------------------------------------------------------------

bool Pile::isCardInPile(Card* pCard)
{
	for (Card* card : mCards)
	{
		if (card == pCard)
		{
			return true;
		}
	}

	return false;
}

// -----------------------------------------------------------------------------

bool Pile::isValidMove(std::vector<Card*>& pCards)
{
	return false;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------