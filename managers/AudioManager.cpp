#include "stdafx.h"
#include "AudioManager.h"

AudioManager::AudioManager(const std::string& folder)
	: m_folder(folder)
{}

AudioManager::~AudioManager()
{
	// Kostyl': fix Mix_FreeMusic(music) bag, when smart pointer freed after Mix_Quit();
	// It was happened only whis mp3 format.
	for (auto& it : m_musicMap)
		it.second.reset();

	Mix_CloseAudio();
	Mix_Quit();
}

bool AudioManager::isSoundExists(const std::string& name) const
{
	return (m_soundMap.find(name) != m_soundMap.end());
}

bool AudioManager::isMusicExists(const std::string& name) const
{
	return (m_musicMap.find(name) != m_musicMap.end());
}

void AudioManager::setSound(const std::string& name)
{
	if (isSoundExists(name))
		return;

	auto tmpPtr = loadSound(getFullFileName(name));

	if (tmpPtr)
	{
		m_soundMap[name] = std::move(tmpPtr);
	}
	else
	{
		std::cerr << "[SOUND_LOAD_ERROR] " << getFullFileName(name) << "\n"
		<< SDL_GetError()
		<< std::endl;
	}
}

void AudioManager::setMusic(const std::string& name)
{
	if (isMusicExists(name))
		return;

	auto tmpPtr = loadMusic(getFullFileName(name));

	if (tmpPtr)
	{
		m_musicMap[name] = std::move(tmpPtr);
	}
	else
	{
		std::cerr << "[MUSIC_LOAD_ERROR] " << getFullFileName(name) << "\n"
		<< SDL_GetError()
		<< std::endl;
	}
}

Mix_Chunk* AudioManager::getSound(const std::string& name) const
{
	if (!isSoundExists(name))
	{
		return (m_soundMap.at("404_sound.wav").get());
	}
	return m_soundMap.at(name).get();
}

Mix_Music* AudioManager::getMusic(const std::string& name) const
{
	if (!isMusicExists(name))
	{
		return (m_musicMap.at("404_music.wav").get());
	}
	return m_musicMap.at(name).get();
}

void AudioManager::playSound(const std::string& name, const int& loops, const int& channel, const int& volume) const
{
	/*
		Play sound effect file
		@param name -		sound effect name in sound map;

		@param loops -		if loops == -1, loop forever,
							otherwise play it loops + 1 times,
							default = 0;

		@param channel -	channel to play on,
							or -1 for the first free unreserved channel, default = -1;
	*/

	Mix_Volume(channel, volume);
	if (Mix_PlayChannel(channel, getSound(name), loops) == -1)
	{	
		std::cerr << "[MIX_PLAYCHANNEL_ERROR] " << Mix_GetError() << std::endl;
	}
}

void AudioManager::playMusic(const std::string& name, const int& loops, const int& volume) const
{
	/*
		Play music file
		@param name -	sound effect name in sound map;

		@param loops -	if loops == -1, loop forever,
						otherwise play it loops times,
						default = -1;
	*/
	Mix_VolumeMusic(volume);
	if (Mix_PlayMusic(getMusic(name), loops) == -1)
	{	
		std::cerr << "[MIX_PLAYMUSIC_ERROR] " << Mix_GetError() << std::endl;
	}
}

void AudioManager::pauseMusic()
{
	if (Mix_PlayingMusic() != 0)
	{
		Mix_PauseMusic();
	}
}

void AudioManager::stopMusic()
{
	Mix_HaltMusic();
}

void AudioManager::resumeMusic()
{
	if (Mix_PausedMusic() != 0)
	{
		Mix_ResumeMusic();
	}
}

void AudioManager::setSoundVolume(const int& channel, const int& volume)
{
	Mix_Volume(channel, volume);
}

void AudioManager::setMusicVolume(const int& volume)
{
	Mix_VolumeMusic(volume);
}

void AudioManager::init()
{
	/*
		Parameter can be a bitwise combination of:
		MIX_INIT_FLAC, MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG
	*/
	int flags = MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG;
	int initted = Mix_Init(flags);
	
	if ((initted&flags) != flags)
	{	
		std::cerr << "[MIX_ERROR] " << Mix_GetError() << std::endl;
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		std::cerr << "[MIX_AUDIO_ERROR] " << Mix_GetError() << std::endl;
	}
	
	Mix_AllocateChannels(16);

	setSound("404_sound.wav");
	setMusic("404_music.wav");
	
	if (isSoundExists("404_sound.wav") && isMusicExists("404_music.wav"))
	{
		m_status = true;
	}
	else
	{
		assert("this is fiasko <T_T> sempai");
	}
}

const bool& AudioManager::getStatus() const
{
	return (m_status);
}

SDLChunkUPtr AudioManager::loadSound(const std::string& path)
{
	auto* rawPtr = Mix_LoadWAV(path.c_str());
	auto deleter = [](Mix_Chunk* chunk)
	{
		Mix_FreeChunk(chunk);
	};

	return (SDLChunkUPtr(rawPtr, deleter));
}

SDLMusicUPtr AudioManager::loadMusic(const std::string& path)
{
	auto* rawPtr = Mix_LoadMUS(path.c_str());
	auto deleter = [](Mix_Music* music)
	{
		Mix_FreeMusic(music);
	};

	return (SDLMusicUPtr(rawPtr, deleter));
}

std::string AudioManager::getFullFileName(const std::string& name)
{
	return (m_folder + name);
}
