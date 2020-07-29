#ifndef STARTSTATE_H_INCLUDE
#define STARTSTATE_H_INCLUDE
#include "State.h"

// ECS includes
#include "ecs/Entity.h"
#include "ecs/EntityManager.h"

class StartState : public State
{
public:
	// Use enum for groups to keep track of our entities
	enum StartStateGroup : std::size_t
	{
		GBackground,
		GButton
	};

	// Constructors/Destructors
	StartState(MainGame& game);
	virtual ~StartState();

	// Functions
	void endState() override;
	void handleInput(const InputManager& input) override;
	void update(const float& deltaTime) override;
	void render(SDL_Renderer& rRender) override;

private:
	// Private functions
	void initStateResources();
	void createStateEntitys();
	void playMusic();
	void createAllButtons();

	// Entity factory
	Entity& createButton(const Vector2f& rPosition, const Vector2f& rSize, const ButtonTextureArray& buttonTextures, std::function<void(void)> function = nullptr);
	Entity& createBackground(const Vector2f& rPosition, const Vector2f& rSize);

private:
	EntityManager m_entityManager;

};

#endif	/*	end STARTSTATE_H_INCLUDE	*/