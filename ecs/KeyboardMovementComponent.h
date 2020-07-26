#ifndef KEYBOARDMOVEMENTCOMPONENT_H_INLCUDE
#define KEYBOARDMOVEMENTCOMPONENT_H_INLCUDE
#include "Component.h"
#include "TransformComponent.h"
#include "AnimationComponent.h"

struct KeyboardMovementComponent : public Component
{
	// Constructor/Destructor
	KeyboardMovementComponent() = default;
	KeyboardMovementComponent(const Vector2f& velocity, const float& acceleration);
	~KeyboardMovementComponent() = default;

	// Functions
	void init() override;
	void update(const float& deltaTime) override;
	void handleInput(const InputManager& input) override;

	void setVelocity(const Vector2f& velocity);
	void setAcceleration(const float& acceleration);

	// Members
	TransformComponent* m_pTransformComp{ nullptr };
	AnimationComponent* m_pAnimationComp{ nullptr };
	Vector2f m_velocity{ 0.0f,0.0f };
	Vector2f m_move{ 0.0f,0.0f };
	float m_acceleration{ 0.0f };
};

#endif	/*	end KEYBOARDMOVEMENTCOMPONENT_H_INLCUDE	*/