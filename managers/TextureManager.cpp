#include "stdafx.h"
#include "TextureManager.h"

TextureManager::TextureManager(const std::string& folder)
	: m_folder(folder)
{}

TextureManager::~TextureManager()
{}

bool TextureManager::isExists(const std::string& name) const
{
	return (m_textureMap.find(name) != m_textureMap.end());
}

SDL_Texture* TextureManager::get(const std::string& name) const
{
	if (!isExists(name))
	{
		return (m_textureMap.at("fiasko.png").get());
	}
	return m_textureMap.at(name).get();
}

Vector2f TextureManager::getTextureSize(const std::string& name) const
{
	int w{ 0 };
	int h{ 0 };

	if (isExists(name))
	{
		SDL_QueryTexture(get(name), nullptr, nullptr, &w, &h);
	}
	return (Vector2f(static_cast<float>(w), static_cast<float>(h)));
}

Vector2f TextureManager::queryTexture(SDL_Texture* texture) const
{
	int w{ 0 };
	int h{ 0 };
	if (texture != nullptr)
	{
		SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	}
	return (Vector2f(static_cast<float>(w), static_cast<float>(h)));
}

void TextureManager::set(SDL_Renderer& rRenderer, const std::string& name)
{
	if (isExists(name))
		return ;
	
	auto tmpPtr = loadTexture(rRenderer, getFullFileName(name));

	if (tmpPtr)
	{
		m_textureMap[name] = std::move(tmpPtr);
	}
	else
	{
		std::cerr << "[TEXTURE_LOAD_ERROR] " << getFullFileName(name) << "\n"
		<< SDL_GetError()
		<< std::endl;
	}
}

void TextureManager::init(SDL_Renderer& rRenderer)
{
	set(rRenderer, "fiasko.png");
	if (isExists("fiasko.png"))
	{
		m_status = true;
	}
	else
		assert("this is fiasko <T_T> sempai");
}

const bool& TextureManager::getStatus() const
{
	return (m_status);
}

// Private functions
SDLTextureUPtr TextureManager::loadTexture(SDL_Renderer& rRenderer, const std::string& path)
{
	auto* rawPtr = IMG_LoadTexture(&rRenderer, path.c_str());
	auto deleter = [](SDL_Texture* texture)
		{
			SDL_DestroyTexture(texture);
		};

	return (SDLTextureUPtr(rawPtr, deleter));
}

std::string TextureManager::getFullFileName(const std::string& name)
{
	return (m_folder + name);
}