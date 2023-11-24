// -----------------------------------------------------------------------------
#ifndef SoundManager_H
#define SoundManager_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <iostream>
#include <map>
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>

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

	// load a music file
	static void loadMusic(const std::string& pMusicFile, const std::string& pFilename)
	{
		auto& instance = getInstance();

		// check if the music file is already loaded
		auto iterator = instance.mMusicTracks.find(pMusicFile);
		if (iterator == instance.mMusicTracks.end())
		{
			// create a new unique pointer to a music track
			std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();

			// try to load the music track
			if (!music->openFromFile(pFilename))
			{
				std::cout << "SoundManager::loadMusic(): Issue loading file " << pFilename << '\n';
				return;
			}
			else
			{
				instance.mMusicTracks.emplace(pMusicFile, std::move(music));
			}
		}
	}

	// play a music file
	static void playMusic(const std::string& pMusicFile)
	{
		auto iterator = getInstance().mMusicTracks.find(pMusicFile);
		if (iterator != getInstance().mMusicTracks.end())
		{
			iterator->second->play();
		}
		else
		{
			std::cout << "SoundManager::playMusic(): Music " << pMusicFile << " was not found.\n";
		}
	}

	// stop a music file
	static void stopMusic(const std::string& pMusicFile)
	{
		auto iterator = getInstance().mMusicTracks.find(pMusicFile);
		if (iterator != getInstance().mMusicTracks.end())
		{
			iterator->second->stop();
		}
		else
		{
			std::cout << "SoundManager::stopMusic(): Music " << pMusicFile << " was not found.\n";
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
	std::map<std::string, std::unique_ptr<sf::Music>> mMusicTracks;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !SoundManager_H