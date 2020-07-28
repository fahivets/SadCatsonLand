#include "stdafx.h"
#include "CameraComponent.h"
#include "Entity.h"

CameraComponent::CameraComponent(const Vector2f& rSize, const Vector2f& worldSize)
{
	m_fRect.w = rSize.x;
	m_fRect.h = rSize.y;
	m_worldSize = worldSize;
}

void CameraComponent::init()
{
	m_pPosComp = &m_entity->getComponent<PositionComponent>();
	m_pSpriteComp = &m_entity->getComponent<SpriteComponent>();
	m_pAnimationComp = &m_entity->getComponent<AnimationComponent>();
	m_pTransformComp = &m_entity->getComponent<TransformComponent>();

	m_fRect.x = m_pPosComp->x() - m_fRect.w / 2;
	m_fRect.y = m_pPosComp->y() - m_fRect.h / 2;
	m_camera = {
		static_cast<int>(m_fRect.x),
		static_cast<int>(m_fRect.y),
		static_cast<int>(m_fRect.w),
		static_cast<int>(m_fRect.h)
	};
}

void CameraComponent::update(const float& deltaTime)
{
	m_fRect.x = m_pPosComp->x() - m_fRect.w / 2;
	m_fRect.y = m_pPosComp->y() - m_fRect.h / 2;
	
	if (m_fRect.x < 0)
	{
		m_fRect.x = 0;
	}
	if (m_fRect.y < 0)
	{
		m_fRect.y = 0;
	}
	if (m_fRect.x > m_worldSize.x - m_fRect.w)
	{
		m_fRect.x = m_worldSize.x - m_fRect.w;
	}
	if (m_fRect.y > m_worldSize.y - m_fRect.h)
	{
		m_fRect.y = m_worldSize.y - m_fRect.h;
	}
	m_camera = {
		static_cast<int>(m_fRect.x),
		static_cast<int>(m_fRect.y),
		static_cast<int>(m_fRect.w),
		static_cast<int>(m_fRect.h)
	};


//	m_pTransformComp->addPosition(-m_fRect.x, -m_fRect.y);

//	m_pSpriteComp->m_pBoxComp->m_fRect.x -= m_fRect.x;
//	m_pSpriteComp->m_pBoxComp->m_fRect.y -= m_fRect.y;
	m_pSpriteComp->m_dstFRect.x -= m_fRect.x;
	m_pSpriteComp->m_dstFRect.y -= m_fRect.y;

//	m_pAnimationComp->m_currPos.x = m_fRect.x;
//	m_pAnimationComp->m_currPos.y = m_fRect.y;
}

void CameraComponent::render(SDL_Renderer& rRender)
{
	SDL_FRect fRect = m_fRect;
	fRect.x -= m_fRect.x;
	fRect.y -= m_fRect.y;

	SDL_SetRenderDrawColor(&rRender, 0, 255, 0, 255);
	SDL_RenderDrawRectF(&rRender, &m_fRect);
	SDL_SetRenderDrawColor(&rRender, 0, 0, 0, 255);
}

float  CameraComponent::x() const noexcept
{
	return (m_fRect.x);
}

float CameraComponent::y() const noexcept
{
	return (m_fRect.y);
}

float  CameraComponent::w() const noexcept
{
	return (m_fRect.w);
}

float  CameraComponent::h() const noexcept
{
	return (m_fRect.h);
}

float  CameraComponent::xCenter() const noexcept
{
	return (m_pPosComp->x());
}

float  CameraComponent::yCenter() const noexcept
{
	return (m_pPosComp->y());
}

float  CameraComponent::left() const noexcept
{
	return (xCenter() - (w() / 2));
}

float  CameraComponent::right() const noexcept
{
	return (xCenter() + (w() / 2));
}

float  CameraComponent::top() const noexcept
{
	return (yCenter() - (h() / 2));
}

float  CameraComponent::bottom() const noexcept
{
	return (yCenter() + (h() / 2));
}
