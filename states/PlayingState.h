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
		GWorld,
		GPlayer,
		GEnemy,
		GBullet
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
	void restart();
	void updateCameraPositions();
	void enemysSpawnerUpdate();

	// Entity factory
	Entity& createWorld(const Vector2f& rPosition, const Vector2f& rSize, const std::string& textureName);
	Entity& createPlayer(const Vector2f& rPosition, const Vector2f& rSize, const std::string& textureName);
	std::shared_ptr<Animation> createAnimations(const FrameData& animationFrameData, const std::string& spriteTextureName, int rows = 1);
	Entity& createEnemy(const Vector2f& rPosition, const Vector2f& rSize);
	Entity& createCamera(const Vector2f& rPosition, const Vector2f& rSize);
	Entity& createBullet(const Vector2f& rPosition, const Vector2f& rSize, const float& angleDir, const std::string& textureName);

	void spawnEnemy(const Vector2f& playerPos, const float& minDistanceToThePlayer);

	void fire();

	template <class T1, class T2>
	bool isIntersecting(T1& rA, T2& rB) noexcept;

private:
	// Members
	bool m_gameOver{ false };
	EntityManager m_entityManager;
	Entity* m_world{ nullptr };
	Entity* m_player{ nullptr };
	Entity* m_camera{ nullptr };

	Vector2f m_worldSize{ 0.0f, 0.0f};
	std::string m_worldName;
	unsigned int m_maxEnemies{ 0 };
	float m_enemySpawnTimerMax{ 0.0f };
	float m_enemySpawnTimer{ 0.0f };
	// TODO: thake this var from console
	unsigned int m_numEnemys{ 10 };
	unsigned int m_numAmmo{ 3 };
};

// Template functions
template <class T1, class T2>
bool PlayingState::isIntersecting(T1& rA, T2& rB) noexcept
{
	return (rA.right() >= rB.left() && rA.left() <= rB.right() &&
		rA.bottom() >= rB.top() && rA.top() <= rB.bottom());
}
#endif	/*	end PLAYINGSTATE_H_INLCUDE	*/