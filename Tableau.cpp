// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Tableau.h"

#include "Card.h"
#include "TextureManager.h"

#include <iostream>

// -----------------------------------------------------------------------------

namespace TableauPrivate
{
	constexpr float Y_OFFSET = 30.f;
}

// -----------------------------------------------------------------------------

Tableau::Tableau(const sf::Vector2f& pPosition)
	: Pile(pPosition)
{
	mBlankSpace.setTexture(TextureManager::getTexture("Graphics/BackDesign.png"));
	mBlankSpace.setScale(0.2f, 0.2f);
	mBlankSpace.setColor(sf::Color(27, 18, 18, 100));
	setPosition(pPosition);
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

void Tableau::push(Card* pCard)
{
	if (getCards().empty())
	{
		Pile::push(pCard);
		return;
	}

	// get the position of the top card
	Card* topCard = peek();
	if (topCard)
	{
		const sf::Vector2f topPos = peek()->getSprite().getPosition();

		pCard->getSprite().setPosition(sf::Vector2f(topPos.x, topPos.y + TableauPrivate::Y_OFFSET));
		getCards().push_back(pCard);
	}	
}

// -----------------------------------------------------------------------------

bool Tableau::isMouseOverTopCard(const sf::Vector2f& pMousePos)
{
	if (!isEmpty())
	{
		return Pile::isMouseOverTopCard(pMousePos);
	}
	else if(mBlankSpace.getGlobalBounds().contains(pMousePos))
	{
		return true;
	}

	return false;
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
		for(uint32_t i = 0; i < getCards().size(); ++i)
		{
			getCards()[i]->render(pWindow);
		}
	}
	else
	{
		pWindow.draw(mBlankSpace);
	}
}

// -----------------------------------------------------------------------------

void Tableau::setStartingPositions()
{
	const float startY = getPosition().y;
	const float offset = 20.f;

	for (uint32_t i = 0; i < getCards().size(); ++i)
	{
		if (i == 0)
		{
			mBlankSpace.setPosition(sf::Vector2f(getPosition().x, startY + offset * i));
		}
		getCards()[i]->setPosition(sf::Vector2f(getPosition().x, startY + offset * i));
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

