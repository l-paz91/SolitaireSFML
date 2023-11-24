// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Foundation.h"

#include "TextureManager.h"

#include <iostream>

// -----------------------------------------------------------------------------

Foundation::Foundation(const sf::Vector2f& pPosition)
	: Pile(pPosition)
{
	mBlankSpace.setTexture(TextureManager::getTexture("Graphics/CardSpritesheet.png"));
	mBlankSpace.setTextureRect(sf::IntRect(0, 680, 118, 170));
	mBlankSpace.setColor(sf::Color(27, 18, 18, 100));
	setPosition(pPosition);

	setPileType(EPileType::eFOUNDATION);
}

// -----------------------------------------------------------------------------

Foundation::~Foundation()
{

}

// -----------------------------------------------------------------------------

bool Foundation::isMouseOverTopCard(const sf::Vector2f& pMousePos)
{
	if (mBlankSpace.getGlobalBounds().contains(pMousePos))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// -----------------------------------------------------------------------------

bool Foundation::isValidMove(Card* pCard)
{
	// if the foundation is empty, only an ace can be moved
	if (isEmpty())
	{
		if (pCard->getRank() == ECardRank::eACE)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// if the pile is not empty, check if the card is the same suit and one rank higher
	if (pCard->getSuit() == peek()->getSuit() && pCard->getRank() == peek()->getRank() + 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// -----------------------------------------------------------------------------

bool Foundation::isValidMove(std::vector<Card*>& pCards)
{
	// we can only move one card at a time to the foundation
	if (pCards.size() != 1)
	{
		return false;
	}

	// if the foundation is empty, only an ace can be moved
	if (isEmpty())
	{
		if (pCards[0]->getRank() == ECardRank::eACE)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// if the pile is not empty, check if the card is the same suit and one rank higher
	if (pCards[0]->getSuit() == peek()->getSuit() && pCards[0]->getRank() == peek()->getRank() + 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// -----------------------------------------------------------------------------

void Foundation::printToConsole()
{
	std::cout << "Foundation: " << std::endl;
	Pile::printToConsole();
}

// -----------------------------------------------------------------------------

void Foundation::render(sf::RenderWindow& pWindow)
{
	pWindow.draw(mBlankSpace);

	if (!getCards().empty())
	{
		if (getCards().back()->isSelected() && getCards().size() > 1)
		{
			// render the card below it instead
			getCards()[getCards().size() - 2]->render(pWindow);
		}

		getCards().back()->render(pWindow);		
	}
}

// -----------------------------------------------------------------------------

void Foundation::render(sf::RenderTexture& pRenderTexture)
{
	pRenderTexture.draw(mBlankSpace);

	if (!getCards().empty())
	{
		pRenderTexture.draw(getCards().back()->getSprite());
	}
}

// -----------------------------------------------------------------------------

ECardSuit Foundation::getSuit()
{
	if (!isEmpty())
	{
		return getCards().back()->getSuit();
	}
	else
	{
		return ECardSuit::eNONE;
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------