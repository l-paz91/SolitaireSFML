// -----------------------------------------------------------------------------
#ifndef Card_H
#define Card_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

// -----------------------------------------------------------------------------

enum ECardRank
{
	eACE = 1,
	eTWO, eTHREE, eFOUR, eFIVE, eSIX, eSEVEN, eEIGHT, eNINE, eTEN,
	eJACK, eQUEEN, eKING
};

// -----------------------------------------------------------------------------

enum ECardSuit
{
	eHEARTS,
	eDIAMONDS,
	eCLUBS,
	eSPADES
};

// -----------------------------------------------------------------------------

class Card
{
public:
	Card(ECardRank pRank, ECardSuit pSuit, bool pFaceUp, std::string pFilename);
	~Card();

	// core basics
	void update(sf::Time& pDeltaTime);
	void render(sf::RenderWindow& pWindow);

	// flips the card from face-down to face-up or vice versa
	void flip();

private:
	sf::Sprite mSprite;
	std::string mTextureFilename;

	ECardRank mRank;
	ECardSuit mSuit;
	bool mFaceUp;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Card_H