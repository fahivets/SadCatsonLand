#include "stdafx.h"
#include "PhysicsComponent.h"
#include "Entity.h"

void PhysicsComponent::init()
{
	m_pPosComp = &m_entity->getComponent<PositionComponent>();
	m_pBoxComp = &m_entity->getComponent<BoxComponent>();
	m_pSpriteComp = &m_entity->getComponent<SpriteComponent>();
	m_startPos = m_pPosComp->m_position;
}

void PhysicsComponent::update(const float& deltaTime)
{
	Vector2f move = {
		m_velocity.x * cosf(toRadians(m_pSpriteComp->m_angle)),
		m_velocity.y * sinf(toRadians(m_pSpriteComp->m_angle))
	};

	m_pPosComp->m_position += move * deltaTime;

	if (m_pPosComp->m_position.x < 0 || m_pPosComp->m_position.x > m_worldSize.x
		|| m_pPosComp->m_position.y < 0 || m_pPosComp->m_position.y > m_worldSize.y)
	{
		m_entity->destroy();
	}
}

BoxComponent& PhysicsComponent::box() const
{
	return (*m_pBoxComp);
}