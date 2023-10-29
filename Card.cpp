// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Card.h"

#include "GameFacilities.h"
#include "TextureManager.h"

// -----------------------------------------------------------------------------

Card::Card(ECardRank pRank, ECardSuit pSuit, bool pFaceUp, std::string pFilename)
	: mTextureFilename(pFilename)
	, mRank(pRank)
	, mSuit(pSuit)
	, mFaceUp(pFaceUp)
{
	// set up card back sprite
	if (!mFaceUp)
	{
		mSprite.setTexture(TextureManager::getTexture(GameFacilities::gCardBackFilename));
	}
	else
	{
		mSprite.setTexture(TextureManager::getTexture(pFilename));
	}

	mSprite.setScale(0.2f, 0.2f);
	mSprite.setPosition(20.f, 20.f);
}

// -----------------------------------------------------------------------------

Card::~Card()
{

}

// -----------------------------------------------------------------------------

void Card::update(sf::Time& pDeltaTime)
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
		mSprite.setTexture(TextureManager::getTexture(GameFacilities::gCardBackFilename));
	}
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


