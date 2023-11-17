// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Card.h"

#include "GameFacilities.h"
#include "TextureManager.h"

#include <SFML/Window/Event.hpp>

// -----------------------------------------------------------------------------

Card::Card(ECardRank pRank, ECardSuit pSuit, bool pFaceUp, const std::string& pFilename)
	: mTextureFilename(pFilename)
	, mRank(pRank)
	, mSuit(pSuit)
	, mFaceUp(pFaceUp)
	, mSelected(false)
{
	// set up card back sprite
	if (!mFaceUp)
	{
		const std::string cardBackFilename = "Graphics/BackDesign.png";
		mSprite.setTexture(TextureManager::getTexture(cardBackFilename));
	}
	else
	{
		mSprite.setTexture(TextureManager::getTexture(pFilename));
	}

	mSprite.setScale(0.2f, 0.2f);
	mSprite.setPosition(20.f, 20.f);

	mPosition = mSprite.getPosition();
}

// -----------------------------------------------------------------------------

Card::~Card()
{

}

// -----------------------------------------------------------------------------

void Card::render(sf::RenderWindow& pWindow)
{
	pWindow.draw(mSprite);
}

// -----------------------------------------------------------------------------

void Card::flip()
{
	mFaceUp = !mFaceUp;

	if (mFaceUp)
	{
		mSprite.setTexture(TextureManager::getTexture(mTextureFilename));
	}
	else
	{
		const std::string cardBackFilename = "Graphics/BackDesign.png";
		mSprite.setTexture(TextureManager::getTexture(cardBackFilename));
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


