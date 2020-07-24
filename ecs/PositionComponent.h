#ifndef POSITIONCOMPONENT_H_INCLUDE
#define POSITIONCOMPONENT_H_INCLUDE
#include "Component.h"

struct PositionComponent : public Component
{
	// Constructor/Destructor
	PositionComponent(const Vector2f& rPosition = { 0.0f, 0.0f });
	~PositionComponent() = default;

	// Functions
	float x() const noexcept;
	float y() const noexcept;
	
	// Members
	Vector2f m_position;
};
#endif	/*	end POSITIONCOMPONENT_H_INCLUDE		*/
