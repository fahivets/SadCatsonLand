#include "stdafx.h"
#include "TransformComponent.h"
#include "Entity.h"



void TransformComponent::init()
{
	m_pPosComp = &m_entity->getComponent<PositionComponent>();
	m_pBoxComp = &m_entity->getComponent<BoxComponent>();
}

void TransformComponent::update(const float& deltaTime)
{
	m_function();
}

void TransformComponent::setPosition(const float& x, const float& y)
{
	m_pPosComp->m_position.x = x;
	m_pPosComp->m_position.y = y;
}

void TransformComponent::setPosition(const Vector2f& pos)
{
	m_pPosComp->m_position = pos;
}

void TransformComponent::addPosition(const float& x, const float& y)
{
	m_pPosComp->m_position.x += x;
	m_pPosComp->m_position.y += y;
}

void TransformComponent::addPosition(const Vector2f& pos)
{
	m_pPosComp->m_position += pos;
}

void TransformComponent::setX(const float& x)
{
	m_pPosComp->m_position.x = x;
}

void TransformComponent::setY(const float& y)
{
	m_pPosComp->m_position.y = y;
}

Vector2f TransformComponent::getPosition() const
{
	return (m_pPosComp->m_position);
}

void TransformComponent::setFunction(std::function<void(void)> function)
{
	m_function = function;
}