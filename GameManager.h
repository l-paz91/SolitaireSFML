// -----------------------------------------------------------------------------
#ifndef GameManager_H
#define GameManager_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Card.h"
#include "Deck.h"
#include "Tableau.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

// -----------------------------------------------------------------------------

class GameManager
{
public:
	GameManager(sf::RenderWindow& pWindow);
	~GameManager();

	void init();

	void processEvents(const sf::Event& pEvent);
	void update(sf::Time& pDeltaTime);
	void render();

	void beginGame();

private:
	sf::Sprite mCardBackSprite;
	sf::RectangleShape mBlankSpace;
	sf::RenderWindow& mWindowRef;

	Deck mDeck;
	std::vector<Tableau> mTableaus;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !GameManager_H