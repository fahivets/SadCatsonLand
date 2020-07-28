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
	m_pCameraComp = &m_entity->getComponent<CameraComponent>();
}

void KeyboardMovementComponent::update(const float& deltaTime)
{
	m_frameMove.x = m_move.x * deltaTime;
	m_frameMove.y = m_move.y * deltaTime;
	m_pTransformComp->addPosition(m_frameMove);
}

void KeyboardMovementComponent::handleInput(const InputManager& input)
{
	Vector2f worldSize = m_pCameraComp->m_worldSize;
	m_move = { 0.0f, 0.0f };

	if (input.keyDown(SDL_SCANCODE_A)  && (m_pBoxComp->left() - 1 > 0))	//move to collision
	{
		m_move.x = -m_velocity.x;
	}
	if (input.keyDown(SDL_SCANCODE_D) && (m_pBoxComp->right() + 1 < worldSize.x))
	{
		m_move.x = m_velocity.x;
	}
	if (input.keyDown(SDL_SCANCODE_W) && (m_pBoxComp->top() - 1 > 0))
	{
		m_move.y = -m_velocity.y;
	}
	if (input.keyDown(SDL_SCANCODE_S) && (m_pBoxComp->bottom() + 1 < worldSize.y))
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
			<< "BOX_wh: " << m_pBoxComp->m_fRect.w << " : " << m_pBoxComp->m_fRect.h << "\n"
			<< "CAM_RECT_pos: " << m_pCameraComp->m_fRect.x << " : " << m_pCameraComp->m_fRect.y << "\n"
			<< "CAM_RECT_wh: " << m_pCameraComp->m_fRect.w << " : " << m_pCameraComp->m_fRect.w << "\n";
	}
}

void KeyboardMovementComponent::setVelocity(const Vector2f& velocity)
{
	m_velocity = velocity;
}