#ifndef BOXCOMPONENT_H_INCLUDE
#define BOXCOMPONENT_H_INCLUDE
#include "Component.h"
#include "PositionComponent.h"

struct BoxComponent : public Component
{
	// Constructor/Destructor
	BoxComponent(const Vector2f& rSize);
	~BoxComponent() = default;

	// Functions
	void init() override;
	void update(const float& deltaTime) override;

	void render(SDL_Renderer& rRender) override; //debag

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
	SDL_FRect m_fRect;

};

#endif	/*	end BOXCOMPONENT_H_INCLUDE		*/