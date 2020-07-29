#ifndef KEYBOARDMOVEMENTCOMPONENT_H_INLCUDE
#define KEYBOARDMOVEMENTCOMPONENT_H_INLCUDE
#include "Component.h"
#include "BoxComponent.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

struct KeyboardMovementComponent : public Component
{
	// Constructor/Destructor
	KeyboardMovementComponent() = default;
	KeyboardMovementComponent(const Vector2f& velocity);
	~KeyboardMovementComponent() = default;

	// Functions
	void init() override;
	void update(const float& deltaTime) override;
	void handleInput(const InputManager& input) override;

	void setVelocity(const Vector2f& velocity);

	// Members
	TransformComponent* m_pTransformComp{ nullptr };
	BoxComponent* m_pBoxComp{ nullptr };

	Vector2f m_velocity{ 0.0f,0.0f };
	Vector2f m_move{ 0.0f,0.0f };
	Vector2f m_frameMove{ 0.0f, 0.0f };
	Vector2f m_worldSize{ 0.0f, 0.0f };
};

#endif	/*	end KEYBOARDMOVEMENTCOMPONENT_H_INLCUDE	*/