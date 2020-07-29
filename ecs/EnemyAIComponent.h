#ifndef ENEMYAICOMPONENT_H_INCLUDE
#define ENEMYAICOMPONENT_H_INCLUDE
#include "Component.h"
#include "PositionComponent.h"
#include "BoxComponent.h"
#include "SpriteComponent.h"

struct EnemyAIComponent : public Component
{
	// Constructor/Destructor
	EnemyAIComponent() = default;
	~EnemyAIComponent() = default;

	// Functions
	void init() override;
	void update(const float& deltaTime) override;

	Vector2f calcSlope(const Vector2f& vec1, const Vector2f& vec2);

	// Members
	PositionComponent* m_pPosComp{ nullptr };
	SpriteComponent* m_pSpriteComp{ nullptr };
	Vector2f m_targetPos{ 0.0f, 0.0f };
};

#endif	/*	end ENEMYAICOMPONENT_H_INCLUDE	*/