#ifndef TEXTURECOMPONENT_H_INCLUDE
#define TEXTURECOMPONENT_H_INCLUDE
#include "Component.h"
#include "BoxComponent.h"

struct TextureComponent : public Component
{
	// Constructor/Destructor
	TextureComponent(SDL_Renderer& rRenderer, const char* textureName);
	~TextureComponent() = default;

	// Functions
	void init() override;
	void render(SDL_Renderer& rRender) override;
	void update(const float& deltaTime) override;

	// Members
	BoxComponent* m_pBoxComp{ nullptr };

	std::string	m_textureName;
	SDL_Texture* m_texture{ nullptr };
	SDL_FRect	m_dstFRect;
};

#endif	/*	end TEXTURECOMPONENT_H_INCLUDE	*/