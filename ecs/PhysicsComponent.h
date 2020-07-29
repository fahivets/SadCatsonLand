#ifndef PHYSICSCOMPONENT_H_INCLUDE
#define PHYSICSCOMPONENT_H_INCLUDE
#include "Component.h"
#include "PositionComponent.h"
#include "BoxComponent.h"
#include "SpriteComponent.h"

struct PhysicsComponent : public Component
{
	// Constructor/Destructor
	PhysicsComponent() = default;
	~PhysicsComponent() = default;

	// Functions
	void init() override;
	void update(const float& deltaTime) override;

	BoxComponent& box() const;
//	Vector2f calcSlope(const Vector2f& vec1, const Vector2f& vec2); //move to -> transformComp
	// Use a callback to handle somthing
	std::function<void(void)> callback{ nullptr };
	
	// Members
	PositionComponent* m_pPosComp{ nullptr };
	BoxComponent* m_pBoxComp{ nullptr };
	SpriteComponent* m_pSpriteComp{ nullptr };
	Vector2f m_dir{ 0.0f, 0.0f };
	Vector2f m_startPos{0.0f, 0.0f};

	Vector2f m_velocity{ 0.0f, 0.0f }; 

};

#endif	/*	end PHYSICSCOMPONENT_H_INCLUDE	*/
