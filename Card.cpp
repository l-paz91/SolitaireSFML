// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Card.h"

#include "GameFacilities.h"
#include "TextureManager.h"

#include <SFML/Window/Event.hpp>

// -----------------------------------------------------------------------------

namespace CardPrivate
{
	// offset into sprite sheet for card back design
	const sf::IntRect cardBackRect(0, 680, 118, 170);
}

// -----------------------------------------------------------------------------

Card::Card(ECardRank pRank, ECardSuit pSuit, bool pFaceUp, const sf::IntRect& pSpritesheetOffset)
	: mSpritesheetOffset(pSpritesheetOffset)
	, mRank(pRank)
	, mSuit(pSuit)
	, mFaceUp(pFaceUp)
	, mSelected(false)
{
	const std::string filename = "Graphics/CardSpritesheet.png";
	mSprite.setTexture(TextureManager::getTexture(filename));

	// set up card back sprite
	if (!mFaceUp)
	{
		mSprite.setTextureRect(CardPrivate::cardBackRect);
	}
	else
	{
		mSprite.setTextureRect(pSpritesheetOffset);
	}

	//mSprite.setScale(0.2f, 0.2f);
	mSprite.setPosition(20.f, 20.f);

	mPosition = mSprite.getPosition();

	// set up the outline
	mOutline.setSize(sf::Vector2f(mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height));
	mOutline.setPosition(mSprite.getPosition());
	mOutline.setFillColor(sf::Color::Yellow);
	mOutline.setOutlineColor(sf::Color::Yellow);
	mOutline.setOutlineThickness(2.f);
}

// -----------------------------------------------------------------------------

Card::~Card()
{

}

// -----------------------------------------------------------------------------

void Card::render(sf::RenderWindow& pWindow)
{
	if (mSelected)
	{
		pWindow.draw(mOutline);
	}

	pWindow.draw(mSprite);
}

// -----------------------------------------------------------------------------

void Card::flip()
{
	mFaceUp = !mFaceUp;

	if (mFaceUp)
	{
		mSprite.setTextureRect(mSpritesheetOffset);
	}
	else
	{
		mSprite.setTextureRect(CardPrivate::cardBackRect);
	}
}

// -----------------------------------------------------------------------------

void Card::printToConsole()
{
	switch (mRank)
	{
	case ECardRank::eACE:
		std::cout << 'A';
		break;
	case ECardRank::eTWO:
		std::cout << '2';
		break;
	case ECardRank::eTHREE:
		std::cout << '3';
		break;
	case ECardRank::eFOUR:
		std::cout << '4';
		break;
	case ECardRank::eFIVE:
		std::cout << '5';
		break;
	case ECardRank::eSIX:
		std::cout << '6';
		break;
	case ECardRank::eSEVEN:
		std::cout << '7';
		break;
	case ECardRank::eEIGHT:
		std::cout << '8';
		break;
	case ECardRank::eNINE:
		std::cout << '9';
		break;
	case ECardRank::eTEN:
		std::cout << "10";
		break;
	case ECardRank::eJACK:
		std::cout << 'J';
		break;
	case ECardRank::eQUEEN:
		std::cout << 'Q';
		break;
	case ECardRank::eKING:
		std::cout << 'K';
		break;
	default:
		break;
	}

	switch (mSuit)
	{
	case ECardSuit::eHEARTS:
		std::cout << 'H';
		break;
	case ECardSuit::eDIAMONDS:
		std::cout << 'D';
		break;
	case ECardSuit::eCLUBS:
		std::cout << 'C';
		break;
	case ECardSuit::eSPADES:
		std::cout << 'S';
		break;
	default:
		break;
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


