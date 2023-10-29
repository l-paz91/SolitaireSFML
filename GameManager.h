// -----------------------------------------------------------------------------
#ifndef GameManager_H
#define GameManager_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Card.h"
#include "Deck.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

// -----------------------------------------------------------------------------

class GameManager
{
public:
	GameManager(sf::RenderWindow& pWindow);
	~GameManager();

	void processEvents(const sf::Event& pEvent);
	void update(sf::Time& pDeltaTime);
	void render();

private:
	sf::Sprite mCardBackSprite;
	sf::RectangleShape mBlankSpace;
	sf::RenderWindow& mWindowRef;

	Deck mDeck;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !GameManager_H