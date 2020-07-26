#include "stdafx.h"
#include "AnimationComponent.h"
#include "Entity.h"

void AnimationComponent::init()
{
	m_pSpriteComp = &m_entity->getComponent<SpriteComponent>();
}

void AnimationComponent::update(const float& deltaTime)
{
	if (m_currentAnimation.first != AnimationState::None)
	{
		bool newFrame = m_currentAnimation.second->updateFrame(deltaTime);
		if (newFrame)
		{
			FrameData data = m_currentAnimation.second->getCurrentFrame();
			m_pSpriteComp->m_srcRect = data.rect;
		}
	}
}

void AnimationComponent::handleInput(const InputManager& input)
{
	Vector2f mousePos = input.mousePos();
	Vector2f currPos = m_pSpriteComp->m_pBoxComp->m_pPosComp->m_position;
	
	m_pSpriteComp->m_angle = toDegrees(atan2(mousePos.y - currPos.y, mousePos.x - currPos.x));
}

void AnimationComponent::addAnimation(AnimationState state, std::shared_ptr<Animation> animation)
{
	m_animationsMap.insert(std::make_pair(state, animation));

	if (m_currentAnimation.first == AnimationState::None)
	{
		setAnimationState(state);
	}
}

void AnimationComponent::setAnimationState(AnimationState state)
{
	if (m_currentAnimation.first == state)
	{
		return ;
	}

	auto animation = m_animationsMap.find(state);
	if (animation != m_animationsMap.end())
	{
		m_currentAnimation.first = animation->first;
		m_currentAnimation.second = animation->second;
		m_currentAnimation.second->reset();
	}
}

const AnimationState& AnimationComponent::getAnimationState() const
{
	return (m_currentAnimation.first);
}