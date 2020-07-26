#ifndef SPRITECOMPONENT_H_INCLUDE
#define SPRITECOMPONENT_H_INCLUDE
#include "Component.h"
#include "BoxComponent.h"
#include "utility/Animation.h"

struct SpriteComponent : public Component
{
	// Constructor/Destructor
	SpriteComponent(SDL_Renderer& rRenderer, const char* spriteName);
	SpriteComponent(SDL_Renderer& rRenderer, const std::string& spriteName);
	~SpriteComponent() = default;

	// Functions
	void init() override;
	void render(SDL_Renderer& rRender) override;
	void update(const float& deltaTime) override;

	// Members
	BoxComponent* m_pBoxComp{ nullptr };
	SDL_Texture* m_spriteTexture{ nullptr };
	SDL_Rect	m_srcRect{ 0 };
	SDL_FRect	m_dstFRect{ 0 };
	float m_angle{ 0.0f };
	// SDL_FLIP_NONE, SDL_FLIP_HORIZONTAL, SDL_FLIP_VERTICAL
	SDL_RendererFlip m_flip{ SDL_FLIP_NONE};
};

#endif /*	end SPRITECOMPONENT_H_INCLUDE	*/