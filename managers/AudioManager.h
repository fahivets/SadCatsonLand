#ifndef AUDIOMANAGER_H_INCLUDE
#define AUDIOMANAGER_H_INCLUDE
#include "utility/NonCopyable.h"
#include "utility/NonMovable.h"

using SDLChunkUPtr = std::unique_ptr<Mix_Chunk, std::function<void(Mix_Chunk*)>>;
using SDLMusicUPtr = std::unique_ptr<Mix_Music, std::function<void(Mix_Music*)>>;

class AudioManager : public NonCopyable, public NonMovable
{
public:
	// Constructors/Destructors
	AudioManager() = delete;
	AudioManager(const std::string& folder);
	~AudioManager();

	// Functions
	bool isSoundExists(const std::string& name) const;
	bool isMusicExists(const std::string& name) const;
	void setSound(const std::string& name);
	void setMusic(const std::string& name);
	Mix_Chunk* getSound(const std::string& name) const;
	Mix_Music* getMusic(const std::string& name) const;
	
	void playSound(const std::string& name, const int& loops = 0, const int& channel = -1, const int& volume = 42) const;
	void playMusic(const std::string& name, const int& loops = -1, const int& volume = 42) const;
	
	void pauseMusic();
	void stopMusic();
	void resumeMusic();

	void setSoundVolume(const int& channel = -1, const int& volume = MIX_MAX_VOLUME);
	void setMusicVolume(const int& volume = MIX_MAX_VOLUME);

	void init();
	const bool& getStatus() const;

private:
	// Private functions
	SDLChunkUPtr loadSound(const std::string& path);
	SDLMusicUPtr loadMusic(const std::string& path);
	std::string getFullFileName(const std::string& name);

private:
	bool m_status{ false };
	const std::string m_folder;
	std::unordered_map<std::string, SDLChunkUPtr> m_soundMap;
	std::unordered_map<std::string, SDLMusicUPtr> m_musicMap;
};

#endif	/*	end AUDIOMANAGER_H_INCLUDE	*/