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
	Vector2f move = { m_velocity.x * cosf(toRadians(m_pSpriteComp->m_angle)), m_velocity.y * sinf(toRadians(m_pSpriteComp->m_angle)) };

	m_pPosComp->m_position += move * deltaTime;

	/*
	Vector2f distance{m_pPosComp->m_position.x - m_startPos.x, m_pPosComp->m_position.y - m_startPos.y};
	float lifeDistance = distance.magnitude();
	*/

	if (m_pPosComp->m_position.x < 0 || m_pPosComp->m_position.x > 1600
		|| m_pPosComp->m_position.y < 0 || m_pPosComp->m_position.y > 1200)
	{
		m_entity->destroy();
	}
}

BoxComponent& PhysicsComponent::box() const
{
	return (*m_pBoxComp);
}
/*
Vector2f PhysicsComponent::calcSlope(const Vector2f& vec1, const Vector2f& vec2)
{
	int steps = static_cast<int>(std::max(abs(vec1.x - vec2.x), abs(vec1.y - vec2.y)));
	Vector2f result{ 0.0f, 0.0f };
	if (steps == 0)
	{
		return (result);
	}
	result.x = vec1.x - vec2.x;
	result.x /= static_cast<float>(steps);

	result.y = vec1.y - vec2.y;
	result.y /= static_cast<float>(steps);

	return (result);
}*/