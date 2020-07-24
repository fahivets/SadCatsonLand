#ifndef UIBUTTONCOMPONENT_H_INCLUDE
#define UIBUTTONCOMPONENT_H_INCLUDE
#include "Component.h"
#include "BoxComponent.h"

using TextureNameArray = std::array<const char*, 3>;
using ButtonTextureArray = std::array<SDL_Texture*, 3>;
using TextureBoxSizeArray = std::array<Vector2f, 3>;

enum ButtonState
{
	NORMAL = 0,
	HOVER = 1,
	PRESSED = 2
};

struct UIButtonComponent : public Component
{

	// Constructor/Destructor
	UIButtonComponent(SDL_Renderer& rRenderer, const TextureNameArray& buttonTextureArray);
	UIButtonComponent(const ButtonTextureArray& buttonTextureArray);
	~UIButtonComponent() = default;

	// Functions
	void init() override;
	void render(SDL_Renderer& rRender) override;
	void update(const float& deltaTime) override;
	void handleInput(const InputManager& input) override;
	void setFunction(std::function<void(void)> function);
	void setTrueButtonBoxSize();
	const ButtonState& getButtonState() const;
	
	// Members
	BoxComponent* m_pBoxComp{ nullptr };
	ButtonTextureArray m_buttonTextureArray;
	ButtonState m_currentState{ ButtonState::NORMAL };
	TextureBoxSizeArray m_buttonsSize;
	std::function<void(void)> m_function = []() {};
};

#endif	/*	end UIBUTTONCOMPONENT_H_INCLUDE		*/
