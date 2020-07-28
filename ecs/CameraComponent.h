#ifndef CAMERACOMPONENT_H_INCLUDE
#define CAMERACOMPONENT_H_INCLUDE
#include "Component.h"
#include"SpriteComponent.h"
#include "PositionComponent.h"
#include "AnimationComponent.h"

#include "TransformComponent.h"

struct CameraComponent : public Component
{
	// Constructor/Destructor
	CameraComponent() = default;
	CameraComponent(const Vector2f& rSize, const Vector2f& worldSize);
	~CameraComponent() = default;

	// Functions
	void init() override;
	void update(const float& deltaTime) override;
	
	void render(SDL_Renderer& rRender) override; // debag

	float x() const noexcept;
	float y() const noexcept;
	float w() const noexcept;
	float h() const noexcept;
	float xCenter() const noexcept;
	float yCenter() const noexcept;
	float left() const noexcept;
	float right() const noexcept;
	float top() const noexcept;
	float bottom() const noexcept;


	// Members
	PositionComponent* m_pPosComp{ nullptr };
	SpriteComponent* m_pSpriteComp{ nullptr };
	AnimationComponent* m_pAnimationComp{ nullptr }; //no?

	TransformComponent* m_pTransformComp{ nullptr };

	SDL_FRect m_fRect;
	SDL_Rect m_camera;
	Vector2f m_worldSize{ 0.0f, 0.0f };
};

#endif /*	end CAMERACOMPONENT_H_INCLUDE	*/