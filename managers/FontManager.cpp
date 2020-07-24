#include "stdafx.h"
#include"FontManager.h"

FontManager::FontManager(const std::string& folder)
	: m_folder(folder)
{}

FontManager::~FontManager()
{
	m_status = false;
}

bool FontManager::isFontExists(const std::string& key) const
{
	return (m_fontsMap.find(key) != m_fontsMap.end());
}

bool FontManager::isTextExists(const std::string& key) const
{
	return (m_textTexturesMap.find(key) != m_textTexturesMap.end());
}

void FontManager::setFont(const std::string& name, const int& fontSize)
{
	std::string key(name + std::to_string(fontSize));

	if (isFontExists(key))
		return ;

	auto tmpPtr = loadFont(getFullFileName(name), fontSize);

	if (tmpPtr)
	{
		m_fontsMap[key] = std::move(tmpPtr);
	}
	else 
	{
		std::cerr << "[FONT_LOAD_ERROR] " << name << "\n"
		<< TTF_GetError() << std::endl;
	}
}

void FontManager::setTextTexture(SDL_Renderer& rRenderer, const std::string& text, const std::string& fontName, const int& size, const SDL_Color& color)
{
	std::string key = text + fontName + std::to_string(size);
	if (isTextExists(key))
		return;
	
	auto tmpPtr = createTextTexture(rRenderer, getFont(fontName, size), text, color);
	if (tmpPtr)
	{
		m_textTexturesMap[key] = std::move(tmpPtr);
	}
	else
	{
		std::cerr << "[TEXT_TEXTURE_CREATE_ERROR] " << key << "\n"
		<< SDL_GetError() << std::endl;
	}
}

TTF_Font* FontManager::getFont(const std::string& name, const int& fontSize)
{
	std::string key(name + std::to_string(fontSize));
	if (!isFontExists(key))
	{
		setFont(name, fontSize);
	}
	return (m_fontsMap.at(key).get());
}

SDL_Texture* FontManager::getText(SDL_Renderer& rRenderer, const std::string& text, const std::string& fontName, const int& size, const SDL_Color& color)
{
	std::string key = text + fontName + std::to_string(size);
	if (!isTextExists(key))
	{
		setTextTexture(rRenderer, text, fontName, size, color);
	}
	return (m_textTexturesMap.at(key).get());
}

Vector2f FontManager::getTextTextureSize(const std::string& text, const std::string& fontName, const int& size) const
{
	int w{ 0 };
	int h{ 0 };
	std::string key = text + fontName + std::to_string(size);
	if (isTextExists(key))
	{
		SDL_QueryTexture(m_textTexturesMap.at(key).get(), nullptr, nullptr, &w, &h);
	}
	return (Vector2f(static_cast<float>(w), static_cast<float>(h)));
}

void FontManager::init()
{
	if (TTF_Init() < 0)
	{
		std::cerr << "[SDL_ERROR] " << SDL_GetError() << std::endl;
	}
	setFont("404_font.ttf", 42);
	m_status = true;
}

const bool& FontManager::getStatus() const
{
	return (m_status);
}

SDLFontUPtr FontManager::loadFont(const std::string& path, const int& fontSize)
{
	auto* rawPtr = TTF_OpenFont(path.c_str(), fontSize);
	auto deleter = [](TTF_Font* font)
		{
			TTF_CloseFont(font);
		};

	return (SDLFontUPtr(rawPtr, deleter));
}

SDLTextureUPtr FontManager::createTextTexture(SDL_Renderer& rRenderer, TTF_Font* font, const std::string& text, const SDL_Color& color)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	
	auto* rawPtr = SDL_CreateTextureFromSurface(&rRenderer, textSurface);
	auto deleter = [](SDL_Texture* texture)
	{
		SDL_DestroyTexture(texture);
	};

	SDL_FreeSurface(textSurface);
	return (SDLTextureUPtr(rawPtr, deleter));
}

std::string FontManager::getFullFileName(const std::string& name)
{
	return (m_folder + name);
}
