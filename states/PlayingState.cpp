#include "stdafx.h"
#include "PlayingState.h"
#include "../MainGame.h"

PlayingState::PlayingState(MainGame& rGame) : State(rGame)
{
	std::cout << "Playing State Constructor" << "\n";
	initStateResources();
	createStateEntitys();
	playMusic();
}

PlayingState::~PlayingState()
{}

void PlayingState::endState()
{

}

void PlayingState::handleInput(const InputManager& input)
{
	if (input.keyDown(SDL_SCANCODE_ESCAPE))
	{
		ResourceHolder::get().audio.pauseMusic();
		ResourceHolder::get().audio.playMusic("opening_theme.mp3");
		needPop(true);
	}
	if (input.mouseButtonDown(LEFT))
	{
		std::cout << "MOUSE PRESSED LEFT" << input.mousePos() << "\n";
	}
	if (input.mouseButtonDown(RIGHT))
	{
		std::cout << "MOUSE PRESSED RIGHT" << input.mousePos() << "\n";
	}

	m_entityManager.handleInput(input);
}

void PlayingState::update(const float& deltaTime)
{
	
	m_entityManager.refresh();
	m_entityManager.update(deltaTime);
	
	/*
	auto& balls(m_entityManager.getEntitiesByGroup(GBall));
	auto& paddles(m_entityManager.getEntitiesByGroup(GPaddle));
	auto& bricks(m_entityManager.getEntitiesByGroup(GBrick));

	for (auto& ball : balls)
	{
		for (auto& paddle : paddles)
		{
			testBPCollision(*ball, *paddle);
		}
		for (auto& brick : bricks)
		{
			testBBCollision(*ball, *brick);
		}
	}
	*/
}

void PlayingState::render(SDL_Renderer& rRender)
{
	m_entityManager.render(rRender);
}

void PlayingState::initStateResources()
{
	// Load textures
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "background_test.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "player_test.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "player_walk.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "player_run.png");

	// Load audio
	ResourceHolder::get().audio.setMusic("lvl_1_theme.mp3");
	ResourceHolder::get().audio.setSound("game_over.mp3");
	ResourceHolder::get().audio.setSound("stage_clear.mp3");
	ResourceHolder::get().audio.setSound("shotgun.wav");
}

void PlayingState::createStateEntitys()
{
	createBackground(
		{ m_pGame->getWinSize().x / 2.0f, m_pGame->getWinSize().y /2.0f },
		m_pGame->getWinSize());
	
	createPlayer({ m_pGame->getWinSize().x / 2.0f, m_pGame->getWinSize().y / 2.0f },
		Vector2f{35,57});
}

void PlayingState::playMusic()
{
	ResourceHolder::get().audio.playMusic("lvl_1_theme.mp3");
}

Entity& PlayingState::createBackground(const Vector2f& rPosition, const Vector2f& rSize)
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<PositionComponent>(rPosition);
	entity.addComponent<BoxComponent>(rSize);
	entity.addComponent<TextureComponent>(m_pGame->getRenderer(), "background_test.png");

	entity.addGroup(PlayingStateGroup::GBackground);

	return (entity);
}

Entity& PlayingState::createPlayer(const Vector2f& rPosition, const Vector2f& rSize)
{
	auto& entity(m_entityManager.addEntity());
	
	entity.addComponent<PositionComponent>(rPosition);
	entity.addComponent<BoxComponent>(rSize);
	
	std::string spriteTextureName = { "player_walk.png" };
	entity.addComponent<SpriteComponent>(m_pGame->getRenderer(), spriteTextureName);


	entity.addComponent<AnimationComponent>();
	auto& animation(entity.getComponent<AnimationComponent>());
	// Create Walking Animations
	FrameData walkingAnimationData;
	walkingAnimationData.id = 6;
	walkingAnimationData.displayTimeSeconds = 60.0f;
	walkingAnimationData.rect = {0, 0, 0, 0};
	animation.addAnimation(AnimationState::Walk, createAnimations(walkingAnimationData, spriteTextureName));
	/*
	// Create Run Animations
	FrameData runAnimationData;
	runAnimationData.id = 6;
	runAnimationData.displayTimeSeconds = 60.0f;
	runAnimationData.rect = { 0, 0, 0, 0 };
	animation.addAnimation(AnimationState::Run, createAnimations(runAnimationData, "player_run.png"));
	*/

	entity.addComponent<TransformComponent>();
	entity.addComponent<KeyboardMovementComponent>(Vector2f{0.2f, 0.2f}, 1.5f);

	entity.addGroup(PlayingStateGroup::GPlayer);
	return (entity);
}

std::shared_ptr<Animation> PlayingState::createAnimations(const FrameData& animationFrameData, const std::string& spriteTextureName)
{
	FrameData data = animationFrameData;
	
	Vector2f spriteTextureSize = ResourceHolder::get().textures.getTextureSize(spriteTextureName);
	Vector2f frameTextureSize{ spriteTextureSize.x / data.id, spriteTextureSize.y };
	data.rect.w = static_cast<int>(frameTextureSize.x);
	data.rect.h = static_cast<int>(frameTextureSize.y);

	std::shared_ptr<Animation> newAnimation = std::make_shared<Animation>();
	for (int frameID = 0; frameID < data.id; ++frameID)
	{
		data.rect.x = data.rect.w * frameID;
		newAnimation->addFrame(frameID, data.rect, data.displayTimeSeconds);
	}

	return (newAnimation);
}


/*
// Entity factory
void PlayingState::createBall()
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<PositionComponent>(Vector2f{ DISPLAY::WINDOW::WIDTH / 2, DISPLAY::WINDOW::HEIGTH / 2 });
	entity.addComponent<BoxComponent>(Vector2f{ BALL::RADIUS * 2, BALL::RADIUS * 2 });
	entity.addComponent<PhysicsComponent>();
	
	//entity.addComponent<RectangleComponent>(SDL_Color{ 255, 0, 0, 255 });

	entity.addComponent<TextureComponent>(m_pGame->getRenderer(), "ball_red.png");

	auto& physics(entity.getComponent<PhysicsComponent>());
	physics.m_velocity = Vector2f{ -BALL::VELOCITY, -BALL::VELOCITY };

	physics.outOfBounds = [&physics](const Vector2f& mSide)
	{
		if (mSide.x != 0.f)
		{
			physics.m_velocity.x = std::abs(physics.m_velocity.x) * mSide.x;
		}
		if (mSide.y != 0.f)
		{
			physics.m_velocity.y = std::abs(physics.m_velocity.y) * mSide.y;
		}
	};

	entity.addGroup(ArkanoidGroup::GBall);
}

void PlayingState::createPaddle()
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<PositionComponent>(Vector2f{ DISPLAY::WINDOW::WIDTH / 2, DISPLAY::WINDOW::HEIGTH - 50 });
	entity.addComponent<BoxComponent>(Vector2f{ PADDLE::WIDTH, PADDLE::HEIGTH });
	entity.addComponent<PhysicsComponent>();

	// TODO tmp rectcomponent
	//entity.addComponent<RectangleComponent>(SDL_Color{ 0, 0, 255, 255 });
	
	entity.addComponent<TextureComponent>(m_pGame->getRenderer(), "paddle_gold.png");
	entity.addComponent<PaddleControlComponent>();
	
	entity.addGroup(ArkanoidGroup::GPaddle);
}

void PlayingState::createBrick(const Vector2f& rPosition)
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<PositionComponent>(rPosition);
	entity.addComponent<BoxComponent>(Vector2f{ BRICK::WIDTH, BRICK::HEIGTH });
	entity.addComponent<PhysicsComponent>();

	// TODO tmp rectcomponent
	//entity.addComponent<RectangleComponent>(SDL_Color{ 255, 255, 0, 255 });

	entity.addComponent<TextureComponent>(m_pGame->getRenderer(), "brick_blue.png");

	entity.addGroup(ArkanoidGroup::GBrick);
}

// Collision
void PlayingState::testBPCollision(Entity& rBall, Entity& rPaddle) noexcept
{
	auto& ball(rBall.getComponent<PhysicsComponent>());
	auto& paddle(rPaddle.getComponent<PhysicsComponent>());

	if (!isIntersecting(ball.box(), paddle.box()))
		return ;

	ball.m_velocity.y = -BALL::VELOCITY;
	if (ball.box().xCenter() < paddle.box().xCenter())
		ball.m_velocity.x = -BALL::VELOCITY;
	else
		ball.m_velocity.x = BALL::VELOCITY;
}

void PlayingState::testBBCollision(Entity& rBall, Entity& rBrick) noexcept
{
	auto& ball(rBall.getComponent<PhysicsComponent>());
	auto& brick(rBrick.getComponent<PhysicsComponent>());

	if (!isIntersecting(ball.box(), brick.box()))
		return;

	rBrick.destroy();

	// How much the ball intersects the brick in every directions
	float overlapLeft{ ball.box().right() - brick.box().left() };
	float overlapRight{ ball.box().left() - brick.box().right() };
	float overlapTop{ ball.box().bottom() - brick.box().top() };
	float overlapBottom{ ball.box().top() - brick.box().bottom() };

	bool ballFromLeft{ abs(overlapLeft) < abs(overlapRight) };
	bool ballFromTop{ abs(overlapTop) < abs(overlapBottom) };

	float minOverlapX{ ballFromLeft ? (overlapLeft) : (overlapRight) };
	float minOverlapY{ ballFromTop ? (overlapTop) : (overlapBottom) };

	if (std::abs(minOverlapX) < std::abs(minOverlapY))
		ball.m_velocity.x = ballFromLeft ? -BALL::VELOCITY : BALL::VELOCITY;
	else
		ball.m_velocity.y = ballFromTop ? -BALL::VELOCITY : BALL::VELOCITY;
}
*/