#ifndef ANIMATIONCOMPONENT_H_INCLUDE
#define ANIMATIONCOMPONENT_H_INCLUDE
#include "Component.h"
#include "SpriteComponent.h"
#include "utility/Animation.h"

enum class AnimationState
{
	None,
	Idle,
	Walk,
	Run,
	Attack
};

struct AnimationComponent : public Component
{
	// Constructor/Destructor
	AnimationComponent() = default;
	~AnimationComponent() = default;

	// Functions
	void init() override;
	void update(const float& deltaTime) override;
	void handleInput(const InputManager& input) override;

	void addAnimation(AnimationState state, std::shared_ptr<Animation> animation);
	void setAnimationState(AnimationState state);
	const AnimationState& getAnimationState() const;

	// Members
	SpriteComponent* m_pSpriteComp{ nullptr };
	std::unordered_map<AnimationState, std::shared_ptr<Animation>> m_animationsMap;
	std::pair<AnimationState, std::shared_ptr<Animation>> m_currentAnimation{ AnimationState::None, nullptr };
};

#endif	/*	end ANIMATIONCOMPONENT_H_INCLUDE	*/