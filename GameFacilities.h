// -----------------------------------------------------------------------------
#ifndef GameFacilities_H
#define GameFacilities_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <ctime>
#include <random>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

// -----------------------------------------------------------------------------

namespace GameFacilities
{
	// -----------------------------------------------------------------------------

	constexpr int gWindowWidth = 1004;
	constexpr int gWindowHeight = 768;

	// -----------------------------------------------------------------------------

	inline int randint(int pMin, int pMax)
	{
		static std::default_random_engine ran((unsigned int)std::time(0));
		return std::uniform_int_distribution<>{pMin, pMax}(ran);
	}

	// -----------------------------------------------------------------------------

	inline int randint(int pMax) { return randint(0, pMax); }

	// -----------------------------------------------------------------------------

	inline float randFloat(float pMin, float pMax)
	{
		static std::default_random_engine ran((unsigned int)std::time(0));
		return static_cast<float>(std::uniform_real_distribution<>{pMin, pMax}(ran));
	}

	// -----------------------------------------------------------------------------

	inline float randFloat(float pMax) { return randFloat(0.f, pMax); }

	// -----------------------------------------------------------------------------

	// set the origin of the text to the centre of it
	static void centreTextOrigin(sf::Text& pText)
	{
		pText.setOrigin(pText.getGlobalBounds().width / 2, 0);
	}

	// -----------------------------------------------------------------------------

	static sf::Vector2f roundVector2f(const sf::Vector2f pVector2f)
	{
		return sf::Vector2f(std::round(pVector2f.x), std::round(pVector2f.y));
	}

	// -----------------------------------------------------------------------------

	static sf::Font getRobotoRegularFont()
	{
		sf::Font font;
		font.loadFromFile("Fonts/Roboto-Regular.ttf");
		return font;
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !GameFacilities_H