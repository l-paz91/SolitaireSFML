// -----------------------------------------------------------------------------
#ifndef TextureManager_H
#define TextureManager_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <iostream>
#include <map>
#include <SFML/Graphics/Texture.hpp>

// -----------------------------------------------------------------------------

class TextureManager
{
public:
	TextureManager(const TextureManager&) = delete;
	void operator=(const TextureManager&) = delete;

	static sf::Texture& getTexture(const std::string& pFilename)
	{
		std::map<std::string, sf::Texture>& ref = getInstance().mTextures;
		auto it = ref.find(pFilename);
		if (it != ref.end())
		{
			return it->second;
		}
		else
		{
			sf::Texture& t = ref[pFilename];
			if (!t.loadFromFile(pFilename))
			{
				std::cout << "Error loading: " << pFilename << std::endl;
			}
			return t;
		}
	}

private:
	TextureManager() {}

	static TextureManager& getInstance()
	{
		static TextureManager instance;	// guaranteed to be destroyed properly
		return instance;
	}

	std::map<std::string, sf::Texture> mTextures;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !TextureManager_H