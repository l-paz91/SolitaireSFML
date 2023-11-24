// -----------------------------------------------------------------------------
#ifndef Card_H
#define Card_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
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
	eSPADES,
	eNONE
};

// -----------------------------------------------------------------------------

class Card
{
public:
	Card(ECardRank pRank, ECardSuit pSuit, bool pFaceUp, const sf::IntRect& pSpritesheetOffset);
	~Card();

	// core basics
	void render(sf::RenderWindow& pWindow);

	// flips the card from face-down to face-up or vice versa
	void flip();

	// print card to console window
	void printToConsole();

	// get sprite
	sf::Sprite& getSprite() { return mSprite; }

	// get rank
	ECardRank getRank() { return mRank; }

	// get suit
	ECardSuit getSuit() { return mSuit; }

	bool isRed() const { return mSuit == eHEARTS || mSuit == eDIAMONDS; }
	bool isBlack() const { return mSuit == eCLUBS || mSuit == eSPADES; }
	bool isFaceUp() const { return mFaceUp; }

	void setPosition(const sf::Vector2f& pPosition) { mSprite.setPosition(pPosition); mPosition = pPosition; }

	void toggleSelected() { mSelected = !mSelected; }
	bool isSelected() const { return mSelected; }
	void setOutlinePosition() { mOutline.setPosition(mSprite.getPosition()); }

private:
	sf::Sprite mSprite;
	sf::RectangleShape mOutline;

	sf::IntRect mSpritesheetOffset;

	sf::Vector2f mPosition;

	ECardRank mRank;
	ECardSuit mSuit;

	bool mFaceUp;
	bool mSelected;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Card_H