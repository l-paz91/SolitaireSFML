// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Deck.h"
#include <iostream>

// -----------------------------------------------------------------------------

Deck::Deck()
	: mStock(sf::Vector2f(20.f, 20.f))
	, mWaste(sf::Vector2f(160.f, 20.f))
{
	const std::string filename = "Graphics/CardSpritesheet.png";

	int xStart = 0;
	int yStart = 0;
	constexpr int width = 118;
	constexpr int height = 170;

	// create a deck of cards
	// heart suit
	for (int rank = ECardRank::eACE; rank < 14; ++rank)
	{
		const sf::IntRect spriteOffset(xStart, yStart, width, height);
		mStock.push(new Card(static_cast<ECardRank>(rank), ECardSuit::eHEARTS, false, spriteOffset));

		xStart += width;
	}

	xStart = 0;
	yStart += height;

	// diamond suit
	for (int rank = ECardRank::eACE; rank < 14; ++rank)
	{
		const sf::IntRect spriteOffset(xStart, yStart, width, height);
		mStock.push(new Card(static_cast<ECardRank>(rank), ECardSuit::eDIAMONDS, false, spriteOffset));

		xStart += width;
	}

	xStart = 0;
	yStart += height;

	// club suit
	for (int rank = ECardRank::eACE; rank < 14; ++rank)
	{
		const sf::IntRect spriteOffset(xStart, yStart, width, height);
		mStock.push(new Card(static_cast<ECardRank>(rank), ECardSuit::eCLUBS, false, spriteOffset));

		xStart += width;
	}

	xStart = 0;
	yStart += height;

	// spade suit
	for (int rank = ECardRank::eACE; rank < 14; ++rank)
	{
		const sf::IntRect spriteOffset(xStart, yStart, width, height);
		mStock.push(new Card(static_cast<ECardRank>(rank), ECardSuit::eSPADES, false, spriteOffset));

		xStart += width;
	}

	// shuffle the deck
	mStock.shuffle();

	//printStockToConsole();

	mWaste.setPileType(EPileType::eWASTE);
	mStock.setPileType(EPileType::eSTOCK);
}

// -----------------------------------------------------------------------------

Deck::~Deck()
{

}

// -----------------------------------------------------------------------------

void Deck::render(sf::RenderWindow& pWindow)
{
	// render the stock pile
	if (!mStock.isEmpty())
	{
		mStock.peek()->render(pWindow);
	}

	// render the waste pile
	if (!mWaste.isEmpty())
	{
		mWaste.peek()->render(pWindow);
	}
}


// -----------------------------------------------------------------------------

void Deck::printStockToConsole()
{
	// print the deck of cards
	std::cout << "Stock: ";
	for (auto* card : mStock.getCards())
	{
		card->printToConsole();
		std::cout << ' ';
	}
	std::cout << '\n';
}

// -----------------------------------------------------------------------------

void Deck::printWasteToConsole()
{
	// print the waste pile
	std::cout << "Waste: ";
	for (auto* card : mWaste.getCards())
	{
		card->printToConsole();
		std::cout << ' ';
	}
	std::cout << '\n';
}

// -----------------------------------------------------------------------------

void Deck::draw()
{
	// can we draw a new card?
	if (mStock.isEmpty())
	{
		// move all cards from the waste back to the stock
		reset();
	}

	// move the top card from the stock to the waste
	mWaste.push(mStock.peek());
	mStock.pop();

	// flip the card so we can see it now
	mWaste.peek()->flip();

	// print the deck of cards
	//printStockToConsole();
	//printWasteToConsole();
}

// -----------------------------------------------------------------------------

void Deck::reset()
{
	// move all cards from the waste back to the stock, flipping them back over again
	while (!mWaste.isEmpty())
	{
		mStock.push(mWaste.peek());
		mStock.peek()->flip();
		mWaste.pop();
	}

	// print the deck of cards
	//printStockToConsole();
	//printWasteToConsole();
}

// -----------------------------------------------------------------------------

bool Deck::isMouseOverStock(const sf::Vector2i& pMousePos)
{
	// check if the mouse is over the stock pile
	if (!mStock.isEmpty())
	{
		const sf::FloatRect& bounds = mStock.peek()->getSprite().getGlobalBounds();

		if (bounds.contains(sf::Vector2f(pMousePos)))
		{
			return true;
		}
	}

	return false;
}

// -----------------------------------------------------------------------------

bool Deck::isMouseOverWaste(const sf::Vector2i& pMousePos)
{
	// check if the mouse is over the waste pile
	if (!mWaste.isEmpty())
	{
		const sf::FloatRect& bounds = mWaste.peek()->getSprite().getGlobalBounds();

		if (bounds.contains(sf::Vector2f(pMousePos)))
		{
			return true;
		}
	}

	return false;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------