#ifndef FONTMANAGER_H_INCLUDE
#define FONTMANAGER_H_INCLUDE
#include "utility/NonCopyable.h"
#include "utility/NonMovable.h"

using SDLFontUPtr = std::unique_ptr<TTF_Font, std::function<void(TTF_Font*)>>;
using SDLTextureUPtr = std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture*)>>;

class FontManager : public NonCopyable, public NonMovable
{
public:
	// Constructors/Destructors
	FontManager() = delete;
	FontManager(const std::string& folder);
	~FontManager();

	// Functions
	bool isFontExists(const std::string& key) const;
	bool isTextExists(const std::string& key) const;
	void setFont(const std::string& name, const int& fontSize);
	void setTextTexture(SDL_Renderer& rRenderer,
		const std::string& text,
		const std::string& fontName, const int& size,
		const SDL_Color& color = {255,255,255});
	
	TTF_Font* getFont(const std::string& name, const int& fontSize);
	SDL_Texture* getText(SDL_Renderer& rRenderer,
		const std::string& text,
		const std::string& fontName, const int& size,
		const SDL_Color& color = { 255,255,255 });

	Vector2f getTextTextureSize(const std::string& text, const std::string& fontName, const int& size) const;

	void init();
	const bool& getStatus() const;

private:
	// Private functions
	SDLFontUPtr loadFont(const std::string& path, const int& fontSize);
	SDLTextureUPtr createTextTexture(SDL_Renderer& rRenderer, TTF_Font* font,const std::string& text,const SDL_Color& color);
	std::string getFullFileName(const std::string& name);

private:
	bool m_status{ false };
	const std::string m_folder;
	std::unordered_map<std::string, SDLFontUPtr> m_fontsMap;
	std::unordered_map<std::string, SDLTextureUPtr> m_textTexturesMap;
};

#endif	/*	end	FONTMANAGER_H_INCLUDE	*/