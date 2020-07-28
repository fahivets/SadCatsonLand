#include "stdafx.h"
#include "BoxComponent.h"
#include "Entity.h"

BoxComponent::BoxComponent(const Vector2f& rSize)
{
	m_fRect.w = rSize.x;
	m_fRect.h = rSize.y;
	// TMP
	std::cout <<"BOX SIZE " << rSize << "\n";
}

void BoxComponent::init()
{
	m_pPosComp = &m_entity->getComponent<PositionComponent>();
	m_fRect.x = m_pPosComp->x() - m_fRect.w / 2;
	m_fRect.y = m_pPosComp->y() - m_fRect.h / 2;
}

void BoxComponent::update(const float& deltaTime)
{
	m_fRect.x = m_pPosComp->x() - m_fRect.w / 2;
	m_fRect.y = m_pPosComp->y() - m_fRect.h / 2;
}
//DEBAG
void BoxComponent::render(SDL_Renderer& rRender)
{
	SDL_SetRenderDrawColor(&rRender, 255, 0, 0, 255);
	SDL_RenderDrawRectF(&rRender, &m_fRect);
	SDL_SetRenderDrawColor(&rRender, 0, 0, 0, 255);
}

float BoxComponent::x() const noexcept
{
	return (m_fRect.x);
}

float BoxComponent::y() const noexcept
{
	return (m_fRect.y);
}

float BoxComponent::w() const noexcept
{
	return (m_fRect.w);
}

float BoxComponent::h() const noexcept
{
	return (m_fRect.h);
}

float BoxComponent::xCenter() const noexcept
{
	return (m_pPosComp->x());
}

float BoxComponent::yCenter() const noexcept
{
	return (m_pPosComp->y());
}

float BoxComponent::left() const noexcept
{
	return (xCenter() - (w() / 2.0f));
}

float BoxComponent::right() const noexcept
{
	return (xCenter() + (w() / 2.0f));
}

float BoxComponent::top() const noexcept
{
	return (yCenter() - (h() / 2.0f));
}

float BoxComponent::bottom() const noexcept
{
	return (yCenter() + (h() / 2.0f));
}