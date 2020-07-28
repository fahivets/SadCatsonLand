#include"stdafx.h"
#include "TextureComponent.h"
#include "Entity.h"

TextureComponent::TextureComponent(SDL_Renderer& rRenderer, const char* textureName)
{
	m_textureName = textureName;
	ResourceHolder::get().textures.set(rRenderer, m_textureName);
	m_texture = ResourceHolder::get().textures.get(m_textureName);

	Vector2f textureSize = ResourceHolder::get().textures.queryTexture(m_texture);
	m_srcRect = {
		0,
		0,
		static_cast<int>(textureSize.x),
		static_cast<int>(textureSize.y)
	};
}

void TextureComponent::init()
{
	m_pBoxComp = &m_entity->getComponent<BoxComponent>();
	m_dstFRect = m_pBoxComp->m_fRect;
}

void TextureComponent::render(SDL_Renderer& rRender)
{
	SDL_RenderCopyF(&rRender, m_texture, &m_srcRect, &m_dstFRect);
}

void TextureComponent::update(const float& deltaTime)
{
	m_dstFRect = m_pBoxComp->m_fRect;
}
