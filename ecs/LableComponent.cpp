#include "stdafx.h"
#include "LableComponent.h"
#include "Entity.h"

LableComponent::LableComponent(SDL_Renderer& rRenderer,
	const std::string& text,
	const std::string& fontName, const int& size,
	const SDL_Color& color)
{
	m_textTexture = ResourceHolder::get().fonts.getText(rRenderer, text, fontName, size, color);
	m_text = text;
	m_fontName = fontName + std::to_string(size);
	m_size = size;
	m_lableColor = color;
	m_lableSize = ResourceHolder::get().textures.queryTexture(m_textTexture);

}

void LableComponent::init()
{
	m_pBoxComp = &m_entity->getComponent<BoxComponent>();
	setTrueLableBoxSize();
}

void LableComponent::render(SDL_Renderer& rRender)
{
	SDL_RenderCopyF(&rRender, m_textTexture, 0, &m_pBoxComp->m_fRect);
}

void LableComponent::setTrueLableBoxSize()
{
	if (m_pBoxComp != nullptr)
	{
		m_pBoxComp->m_fRect.w = m_lableSize.x;
		m_pBoxComp->m_fRect.h = m_lableSize.y;
	}
}
