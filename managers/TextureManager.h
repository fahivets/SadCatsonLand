#ifndef TEXTUREMANAGER_H_INCLUDE
#define TEXTUREMANAGER_H_INCLUDE
#include "utility/NonCopyable.h"
#include "utility/NonMovable.h"

using SDLTextureUPtr = std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture*)>>;

class TextureManager : public NonCopyable, public NonMovable
{
public:
	// Constructors/Destructors
	TextureManager() = delete;
	TextureManager(const std::string& folder);
	~TextureManager();

	// Functions
	bool isExists(const std::string& name) const;
	void set(SDL_Renderer& rRenderer, const std::string& name);
	SDL_Texture* get(const std::string& name) const;
	Vector2f getTextureSize(const std::string& name) const;
	Vector2f queryTexture(SDL_Texture* texture) const;
	void init(SDL_Renderer& rRenderer);
	const bool& getStatus() const;

private:
	// Private functions
	SDLTextureUPtr loadTexture(SDL_Renderer& rRenderer, const std::string& path);
	std::string getFullFileName(const std::string& name);

private:
	bool m_status{ false };
	const std::string m_folder;
	std::unordered_map<std::string, SDLTextureUPtr> m_textureMap;	
};

#endif	/*	end TEXTUREMANAGER_H_INCLUDE	*/