#include "stdafx.h"
#include "EnemyAIComponent.h"
#include "Entity.h"

void EnemyAIComponent::init()
{
	m_pPosComp = &m_entity->getComponent<PositionComponent>();
	m_pSpriteComp = &m_entity->getComponent<SpriteComponent>();
}

void EnemyAIComponent::update(const float& deltaTime)
{
	Vector2f currPos = m_pPosComp->m_position;

	m_pSpriteComp->m_angle = toDegrees(atan2(m_targetPos.y - currPos.y, m_targetPos.x - currPos.x));
}

Vector2f EnemyAIComponent::calcSlope(const Vector2f& vec1, const Vector2f& vec2)
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
}