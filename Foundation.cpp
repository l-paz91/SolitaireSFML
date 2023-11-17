// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Foundation.h"

#include "TextureManager.h"

#include <iostream>

// -----------------------------------------------------------------------------

Foundation::Foundation(const sf::Vector2f& pPosition)
	: Pile(pPosition)
{
	mBlankSpace.setTexture(TextureManager::getTexture("Graphics/BackDesign.png"));
	mBlankSpace.setScale(0.2f, 0.2f);
	mBlankSpace.setColor(sf::Color(27, 18, 18, 100));
	setPosition(pPosition);
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
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------