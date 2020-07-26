#include "stdafx.h"
#include "KeyboardMovementComponent.h"
#include "Entity.h"

KeyboardMovementComponent::KeyboardMovementComponent(const Vector2f& velocity, const float& acceleration)
{
	m_velocity = velocity;
	m_acceleration = acceleration;
}

void KeyboardMovementComponent::init()
{
	m_pTransformComp = &m_entity->getComponent<TransformComponent>();
	m_pAnimationComp = &m_entity->getComponent<AnimationComponent>();
}

void KeyboardMovementComponent::update(const float& deltaTime)
{
	float xFrameMove = m_move.x * deltaTime;
	float yFrameMove = m_move.y * deltaTime;
	m_pTransformComp->addPosition(xFrameMove, yFrameMove);
}

void KeyboardMovementComponent::handleInput(const InputManager& input)
{
	m_move = { 0.0f, 0.0f };
	if (input.keyDown(SDL_SCANCODE_A))
	{
		m_move.x = -m_velocity.x;
	}
	if (input.keyDown(SDL_SCANCODE_D))
	{
		m_move.x = m_velocity.x;
	}
	if (input.keyDown(SDL_SCANCODE_W))
	{
		m_move.y = -m_velocity.y;
	}
	if (input.keyDown(SDL_SCANCODE_S))
	{
		m_move.y = m_velocity.y;
	}
	if (input.keyDown(SDL_SCANCODE_LSHIFT))
	{
		m_move *= m_acceleration;
		m_pAnimationComp->setAnimationState(AnimationState::Run);
	}
	else
	{
		m_pAnimationComp->setAnimationState(AnimationState::Walk);
	}
}

void KeyboardMovementComponent::setVelocity(const Vector2f& velocity)
{
	m_velocity = velocity;
}

void KeyboardMovementComponent::setAcceleration(const float& acceleration)
{
	m_acceleration = acceleration;
}
