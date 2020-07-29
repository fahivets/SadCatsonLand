#include "stdafx.h"
#include "KeyboardMovementComponent.h"
#include "Entity.h"

KeyboardMovementComponent::KeyboardMovementComponent(const Vector2f& velocity)
{
	m_velocity = velocity;
}

void KeyboardMovementComponent::init()
{
	m_pTransformComp = &m_entity->getComponent<TransformComponent>();
	m_pBoxComp = &m_entity->getComponent<BoxComponent>();
//	m_pCameraComp = &m_entity->getComponent<CameraComponent>();
}

void KeyboardMovementComponent::update(const float& deltaTime)
{
	m_frameMove.x = m_move.x * deltaTime;
	m_frameMove.y = m_move.y * deltaTime;

	// tmp outOfBounds check
	Vector2f worldSize{ 1600, 1200 }; // tmp
	Vector2f newPos(m_pTransformComp->getPosition());
	newPos.x += m_frameMove.x;
	newPos.y += m_frameMove.y;
	if (newPos.x - m_pBoxComp->w() / 2.0f < 0)
	{
		newPos.x = m_pBoxComp->w() / 2.0f;
	}
	else if (newPos.x + m_pBoxComp->w() / 2.0f > worldSize.x)
	{
		newPos.x = worldSize.x - m_pBoxComp->w() / 2.0f;
	}
	if (newPos.y - m_pBoxComp->h() / 2.0f < 0)
	{
		newPos.y = m_pBoxComp->h() / 2.0f;
	}
	else if (newPos.y + m_pBoxComp->h() / 2.0f > worldSize.y)
	{
		newPos.y = worldSize.y - m_pBoxComp->h() / 2.0f;
	}
	m_pTransformComp->setPosition(newPos);
}

void KeyboardMovementComponent::handleInput(const InputManager& input)
{
//	Vector2f worldSize = m_pCameraComp->m_worldSize;
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
	// Debag 
	if (input.mouseButtonPressed(LEFT))
	{
		std::cout << m_pBoxComp->m_pPosComp->m_position << "\n";
	}
	if (input.keyPressed(SDL_SCANCODE_I))
	{
		std::cout << "<<<<<[DEBAG_INFO]>>>>>\n"
			<< "POS: " << m_pBoxComp->m_pPosComp->m_position << "\n"
			<< "BOX_pos: " << m_pBoxComp->x() << " : " << m_pBoxComp->y() << "\n"
			<< "BOX_wh: " << m_pBoxComp->m_fRect.w << " : " << m_pBoxComp->m_fRect.h << "\n";
	}
}

void KeyboardMovementComponent::setVelocity(const Vector2f& velocity)
{
	m_velocity = velocity;
}