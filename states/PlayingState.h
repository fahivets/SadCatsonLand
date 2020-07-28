#ifndef PLAYINGSTATE_H_INCLUDE
#define PLAYINGSTATE_H_INLCUDE
#include "State.h"

// ECS includes
#include "ecs/Entity.h"
#include "ecs/EntityManager.h"

class PlayingState : public State
{
public:
	// Use enum for groups to keep track of our entities
	enum PlayingStateGroup : std::size_t
	{
		GCamera,
		GBackground,
		GPlayer,
		GEnemy
	};

	// Constructors/Destructors
	PlayingState(MainGame& rGame);
	virtual ~PlayingState();

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
	
	// Entity factory
	Entity& createBackground(const Vector2f& rPosition, const Vector2f& rSize);
	Entity& createPlayer(const Vector2f& rPosition, const Vector2f& rSize);
	std::shared_ptr<Animation> createAnimations(const FrameData& animationFrameData, const std::string& spriteTextureName, int rows = 1);
	Entity& createEnemy(const Vector2f& rPosition, const Vector2f& rSize);
		/*
	void createBall();
	void createPaddle();
	void createBrick(const Vector2f& rPosition);

	// Collision
	void testBPCollision(Entity& rBall, Entity& rPaddle) noexcept;
	void testBBCollision(Entity& rBall , Entity& rBrick) noexcept;
	*/

	template <class T1, class T2>
	bool isIntersecting(T1& rA, T2& rB) noexcept;

private:
	// Members
	EntityManager m_entityManager;
	Entity* m_world{ nullptr };
	Entity* m_bob{ nullptr };
	Entity* m_player{ nullptr };
};

// Template functions
template <class T1, class T2>
bool PlayingState::isIntersecting(T1& rA, T2& rB) noexcept
{
	return (rA.right() >= rB.left() && rA.left() <= rB.right() &&
		rA.bottom() >= rB.top() && rA.top() <= rB.bottom());
}
#endif	/*	end PLAYINGSTATE_H_INLCUDE	*/