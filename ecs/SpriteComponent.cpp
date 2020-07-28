#include "stdafx.h"
#include "SpriteComponent.h"
#include "Entity.h"

SpriteComponent::SpriteComponent(SDL_Renderer& rRenderer, const char* spriteName)
{
	ResourceHolder::get().textures.set(rRenderer, spriteName);
	m_spriteTexture = ResourceHolder::get().textures.get(spriteName);
	
	Vector2f textureSize = ResourceHolder::get().textures.queryTexture(m_spriteTexture);
	m_srcRect = {
		0,
		0,
		static_cast<int>(textureSize.x),
		static_cast<int>(textureSize.y)
	};
}

SpriteComponent::SpriteComponent(SDL_Renderer& rRenderer, const std::string& spriteName)
{
	ResourceHolder::get().textures.set(rRenderer, spriteName);
	m_spriteTexture = ResourceHolder::get().textures.get(spriteName.c_str());
	
	Vector2f textureSize = ResourceHolder::get().textures.queryTexture(m_spriteTexture);

	m_srcRect = {
		0,
		0,
		static_cast<int>(textureSize.x),
		static_cast<int>(textureSize.y)
	};
}

void SpriteComponent::init()
{
	m_pBoxComp = &m_entity->getComponent<BoxComponent>();
	m_dstFRect = m_pBoxComp->m_fRect;
}

void SpriteComponent::render(SDL_Renderer& rRender)
{
	SDL_RenderCopyExF(&rRender, m_spriteTexture, &m_srcRect, &m_dstFRect, m_angle, nullptr, m_flip);
}

void SpriteComponent::update(const float& deltaTime)
{
	m_dstFRect = m_pBoxComp->m_fRect;
}