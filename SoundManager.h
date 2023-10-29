// -----------------------------------------------------------------------------
#ifndef SoundManager_H
#define SoundManager_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <iostream>
#include <map>
#include <SFML/Audio.hpp>

// -----------------------------------------------------------------------------

class SoundManager
{
public:
	// don't allow copying
	SoundManager(const SoundManager&) = delete;
	void operator=(const SoundManager&) = delete;

	static void loadSound(const std::string& pSoundFile, const std::string& pFilename)
	{
		auto iterator = getInstance().mSoundBuffers.find(pSoundFile);
		if (iterator == getInstance().mSoundBuffers.end())
		{
			// construct a new sound buffer in place in the map
			auto [bufferIterator, bufferInserted] = getInstance().mSoundBuffers.emplace(pSoundFile, sf::SoundBuffer());

			if (!bufferIterator->second.loadFromFile(pFilename))
			{
				std::cout << "SoundManager::loadSound(): Issue loading file " << pFilename << '\n';
				getInstance().mSoundBuffers.erase(bufferIterator);
				return;
			}

			// construct a new sound in place
			auto [soundIterator, soundInserted] = getInstance().mSounds.emplace(pSoundFile, sf::Sound());
			soundIterator->second.setBuffer(bufferIterator->second);
		}
	}

	static void playSound(const std::string& pSoundFile)
	{
		auto iterator = getInstance().mSounds.find(pSoundFile);
		if (iterator != getInstance().mSounds.end())
		{
			iterator->second.play();
		}
		else
		{
			std::cout << "SoundManager::playSound(): Sound " << pSoundFile << " was not found.\n";
		}
	}

private:
	SoundManager() {}

	static SoundManager& getInstance()
	{
		static SoundManager instance;
		return instance;
	}

	std::map<std::string, sf::SoundBuffer> mSoundBuffers;
	std::map<std::string, sf::Sound> mSounds;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !SoundManager_H