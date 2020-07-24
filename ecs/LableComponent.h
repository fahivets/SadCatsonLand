#ifndef LABLECOMPONENT_H_INCLUDE
#define LABLECOMPONENT_H_INCLUDE
#include "Component.h"
#include "BoxComponent.h"

struct LableComponent : public Component
{
	// Constructor/Destructor
	LableComponent(SDL_Renderer& rRenderer,
		const std::string& text,
		const std::string& fontName, const int& size,
		const SDL_Color& color = {255, 255, 255});
	~LableComponent() = default;

	// Functions
	void init() override;
	virtual void render(SDL_Renderer& rRender) override;
	void setTrueLableBoxSize();

	// Members
	BoxComponent* m_pBoxComp{ nullptr };
	SDL_Texture* m_textTexture{ nullptr };
	std::string m_text;
	std::string m_fontName;
	int m_size;
	SDL_Color m_lableColor;
	Vector2f m_lableSize;
};

#endif	/*	end LABLECOMPONENT_H_INCLUDE	*/

