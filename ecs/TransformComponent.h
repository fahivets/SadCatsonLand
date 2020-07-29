#ifndef TRANSFORMCOMPONENT_H_INCLUDE
#define TRANSFORMCOMPONENT_H_INCLUDE
#include "Component.h"
#include "PositionComponent.h"
#include "BoxComponent.h"

struct TransformComponent : public Component
{
	// Constructor/Destructor
	TransformComponent() = default;
	~TransformComponent() = default;

	// Functions
	void init() override;
	virtual void update(const float& deltaTime) override;

	void setPosition(const float& x, const float& y);
	void setPosition(const Vector2f& pos);
	void addPosition(const float& x, const float& y);
	void addPosition(const Vector2f& pos);
	void setX(const float& x);
	void setY(const float& y);
	Vector2f getPosition() const;
	void setFunction(std::function<void(void)> function);

	// Members
	PositionComponent* m_pPosComp{ nullptr };
	BoxComponent* m_pBoxComp{ nullptr };
	std::function<void(void)> m_function = []() {};
};

#endif	/*	end TRANSFORMCOMPONENT_H_INLCUDE*/
