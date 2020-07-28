#include "stdafx.h"
#include "PlayingState.h"
#include "../MainGame.h"

PlayingState::PlayingState(MainGame& rGame) : State(rGame)
{
	std::cout << "Playing State Constructor" << "\n";
	initStateResources();
	createStateEntitys();
//	playMusic();
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

	if (input.mouseButtonPressed(LEFT))
	{
		ResourceHolder::get().audio.playSound("shotgun.wav", 0, 1);
	}
	if (input.mouseButtonDown(RIGHT))
	{
		std::cout << "MOUSE_POS: " << input.mousePos() << "\n";
	}

	m_entityManager.handleInput(input);
}

void PlayingState::update(const float& deltaTime)
{
	
	m_entityManager.refresh();
	m_entityManager.update(deltaTime);

	auto& camera(m_player->getComponent<CameraComponent>());
	auto& backgrounds(m_entityManager.getEntitiesByGroup(GBackground));
	auto& enemys(m_entityManager.getEntitiesByGroup(GEnemy));

	for (auto& bg : backgrounds)
	{
		auto& bgTexture(bg->getComponent<SpriteComponent>());
		bgTexture.m_srcRect = camera.m_camera;//

	//	auto& bgPos(bg->getComponent<TransformComponent>());
	//	bgPos.addPosition(-camera.m_fRect.x, -camera.m_fRect.y);
		bgTexture.m_dstFRect.w = camera.m_fRect.w;//
		bgTexture.m_dstFRect.h = camera.m_fRect.h;//
	}

	auto& pBox(m_player->getComponent<BoxComponent>());
	for (auto& enemy : enemys)
	{
		auto& bBox(enemy->getComponent<BoxComponent>());
		if (isIntersecting(pBox, bBox))
		{
		//	enemy->destroy();
			std::cout << "INTERSECT enemy" << "\n";
		}	
	}
}

void PlayingState::render(SDL_Renderer& rRender)
{
	m_entityManager.render(rRender);

}

void PlayingState::initStateResources()
{
	// Load textures
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "background_test.png");

	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "player.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "player_walk.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "player_run.png");

	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "mob_5.png");

	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "player_sprite.png");

	// Load audio
	ResourceHolder::get().audio.setMusic("lvl_1_theme.mp3");
	ResourceHolder::get().audio.setSound("game_over.mp3");
	ResourceHolder::get().audio.setSound("stage_clear.mp3");
	ResourceHolder::get().audio.setSound("shotgun.wav");
}

void PlayingState::createStateEntitys()
{
	Vector2f worldSize = ResourceHolder::get().textures.getTextureSize("background_test.png");
	
	m_world = &createBackground( {worldSize.x / 2,worldSize.y / 2 }, worldSize);
	m_player = &createPlayer({worldSize.x / 2, 60 }, Vector2f{ 66,60 });
	
	//m_bob = &createEnemy({ worldSize.x / 2, worldSize.y / 2 }, Vector2f{ 32,32 });
	m_bob = &createEnemy({ worldSize.x / 2, 300 }, Vector2f{ 32,32 });
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
	entity.addComponent<SpriteComponent>(m_pGame->getRenderer(), "background_test.png");
	entity.addComponent<TransformComponent>();
	entity.addGroup(PlayingStateGroup::GBackground);

	return (entity);
}

Entity& PlayingState::createPlayer(const Vector2f& rPosition, const Vector2f& rSize)
{
	auto& entity(m_entityManager.addEntity());
	
	entity.addComponent<PositionComponent>(rPosition);
	entity.addComponent<BoxComponent>(rSize);
	
	std::string spriteTextureName = { "player.png" };
	entity.addComponent<SpriteComponent>(m_pGame->getRenderer(), spriteTextureName);

	entity.addComponent<AnimationComponent>();
	auto& animation(entity.getComponent<AnimationComponent>());
	// Create walk animation
	FrameData walkAnimationData;
	walkAnimationData.id = 1;
	walkAnimationData.displayTimeMSeconds = 0.0f;
	walkAnimationData.rect = { 0, 0, 0, 0 };
	animation.addAnimation(AnimationState::Walk, createAnimations(walkAnimationData, spriteTextureName, 1));
	
	entity.addComponent<TransformComponent>();

	entity.addComponent<CameraComponent>(Vector2f{ 800,600 }, Vector2f{840, 1300});
	entity.addComponent<KeyboardMovementComponent>(Vector2f{0.2f, 0.2f});

	entity.addGroup(PlayingStateGroup::GPlayer);
	return (entity);
}

std::shared_ptr<Animation> PlayingState::createAnimations(const FrameData& animationFrameData, const std::string& spriteTextureName, int rows)
{
	FrameData data = animationFrameData;
	
	Vector2f spriteTextureSize = ResourceHolder::get().textures.getTextureSize(spriteTextureName);
	Vector2f frameTextureSize{ spriteTextureSize.x / data.id, spriteTextureSize.y / rows };
	data.rect.w = static_cast<int>(frameTextureSize.x);
	data.rect.h = static_cast<int>(frameTextureSize.y);
	std::shared_ptr<Animation> newAnimation = std::make_shared<Animation>();
	for (int frameID = 0; frameID < data.id; ++frameID)
	{
		data.rect.x = data.rect.w * frameID;
		newAnimation->addFrame(frameID, data.rect, data.displayTimeMSeconds);
	}

	return (newAnimation);
}

Entity& PlayingState::createEnemy(const Vector2f& rPosition, const Vector2f& rSize)
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<PositionComponent>(rPosition);
	entity.addComponent<BoxComponent>(rSize);

	std::string spriteTextureName = { "mob_5.png" };
	entity.addComponent<SpriteComponent>(m_pGame->getRenderer(), spriteTextureName);
	entity.addComponent<TransformComponent>();

	entity.addGroup(PlayingStateGroup::GEnemy);
	return (entity);
}
