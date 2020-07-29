#include "stdafx.h"
#include "PlayingState.h"
#include "../MainGame.h"

PlayingState::PlayingState(MainGame& rGame) : State(rGame)
{
	initStateResources();
	createStateEntitys();
	playMusic();

	m_maxEnemies = 10;
	m_enemySpawnTimerMax = 60.0f;
	m_enemySpawnTimer = 0.0f;
	// TODO: thake this var from console
	m_numEnemys = 10;
	m_numAmmo = 3;
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
		fire();
	}

	m_entityManager.handleInput(input);
}

void PlayingState::update(const float& deltaTime)
{	
	if (!Mix_Playing(2))
		playMusic();
	m_entityManager.refresh();
	m_entityManager.update(deltaTime);

	auto& enemys(m_entityManager.getEntitiesByGroup(GEnemy));
	auto& bullets(m_entityManager.getEntitiesByGroup(GBullet));
	auto& playerBox(m_player->getComponent<BoxComponent>());
	auto& cameraBox(m_camera->getComponent<BoxComponent>());

	updateCameraPositions();

	// Enemys update position and check intersction
	for (auto& enemy : enemys)
	{
		auto& enemyBox(enemy->getComponent<BoxComponent>());
		auto& enemySprite(enemy->getComponent<SpriteComponent>());
		auto& enemyAI(enemy->getComponent<EnemyAIComponent>());
		enemySprite.m_dstFRect.x = enemyBox.x() - cameraBox.m_fRect.x;
		enemySprite.m_dstFRect.y = enemyBox.y() - cameraBox.m_fRect.y;
		enemyAI.m_targetPos = playerBox.m_pPosComp->m_position;

		if (isIntersecting(enemyBox, playerBox))
		{
			restart();
		}
	}

	// Bullets update position and check intersction
	for (auto& bullet : bullets)
	{
		auto& bulletBox(bullet->getComponent<BoxComponent>());
		auto& sprite(bullet->getComponent<SpriteComponent>());
		sprite.m_dstFRect.x = bulletBox.x() - cameraBox.m_fRect.x;
		sprite.m_dstFRect.y = bulletBox.y() - cameraBox.m_fRect.y;
		for (auto& enemy : enemys)
		{
			auto& enemyBox(enemy->getComponent<BoxComponent>());
			if (isIntersecting(enemyBox, bulletBox))
			{
				enemy->destroy();
				bullet->destroy();
			}
		}
	}

	enemysSpawnerUpdate();
}

void PlayingState::render(SDL_Renderer& rRender)
{
	m_entityManager.render(rRender);
}

void PlayingState::initStateResources()
{
	// Load textures
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "player.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "mob_5.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "bullet.png");

	//Load lvl textures
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "lvl_1212_800.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "lvl_1600_1200.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "lvl_840_1300.png");
	m_worldName = { "lvl_840_1300.png" };
	// Load audio
	ResourceHolder::get().audio.setMusic("lvl_1_theme.mp3");
	ResourceHolder::get().audio.setSound("game_over.mp3");
	ResourceHolder::get().audio.setSound("stage_clear.mp3");
	ResourceHolder::get().audio.setSound("shotgun.wav");
}

void PlayingState::createStateEntitys()
{
	// Create wolrd

	m_worldSize = ResourceHolder::get().textures.getTextureSize(m_worldName);
	m_world = &createWorld({ m_worldSize.x / 2.0f, m_worldSize.y /2.0f }, m_worldSize, m_worldName);

	// Create player
	Vector2f playerPos{ m_worldSize.x / 2,  m_worldSize.y / 2 };
	Vector2f playerSize = ResourceHolder::get().textures.getTextureSize("player.png"); 
	m_player = &createPlayer(playerPos, playerSize, "player.png");
	
	// Create camera
	m_camera = &createCamera(playerPos, m_worldSize);

}

void PlayingState::playMusic()
{	
	if (!Mix_PlayingMusic())
		ResourceHolder::get().audio.playMusic("lvl_1_theme.mp3");
}

void PlayingState::restart()
{
	ResourceHolder::get().audio.stopMusic();
	ResourceHolder::get().audio.playSound("game_over.mp3", 0, 2, 50);

	auto& enemys(m_entityManager.getEntitiesByGroup(GEnemy));
	auto& bullets(m_entityManager.getEntitiesByGroup(GBullet));

	for (auto& enemy : enemys)
	{
		enemy->destroy();
	}
	for (auto& bullet : bullets)
	{
		bullet->destroy();
	}
	auto& playerPos(m_player->getComponent<PositionComponent>());
	playerPos.m_position = {m_worldSize.x / 2.0f, m_worldSize.y / 2.0f};

}

void PlayingState::updateCameraPositions()
{
	auto& playerBox(m_player->getComponent<BoxComponent>());
	auto& cameraBox(m_camera->getComponent<BoxComponent>());
	
	cameraBox.m_fRect.x = playerBox.xCenter() - cameraBox.xCenter();
	cameraBox.m_fRect.y = playerBox.yCenter() - cameraBox.yCenter();
	if (cameraBox.x() < 0)
	{
		cameraBox.m_fRect.x = 0;
	}
	if (cameraBox.y() < 0)
	{
		cameraBox.m_fRect.y = 0;
	}
	if (cameraBox.x() > m_worldSize.x - cameraBox.w())
	{
		cameraBox.m_fRect.x = m_worldSize.x - cameraBox.w();
	}
	if (cameraBox.y() > m_worldSize.y - cameraBox.h())
	{
		cameraBox.m_fRect.y = m_worldSize.y - cameraBox.h();
	}

	auto& playerSprite(m_player->getComponent<SpriteComponent>());
	playerSprite.m_dstFRect.x = playerBox.x() - cameraBox.m_fRect.x;
	playerSprite.m_dstFRect.y = playerBox.y() - cameraBox.m_fRect.y;

	// fix mousepos
	auto& pAnim(m_player->getComponent<AnimationComponent>());
	pAnim.m_offset.x = cameraBox.m_fRect.x;
	pAnim.m_offset.y = cameraBox.m_fRect.y;

	auto& worldTexture(m_world->getComponent<SpriteComponent>());
	worldTexture.m_dstFRect.w = cameraBox.w();
	worldTexture.m_dstFRect.h = cameraBox.h();
	worldTexture.m_srcRect.x = static_cast<int>(cameraBox.x());
	worldTexture.m_srcRect.y = static_cast<int>(cameraBox.y());
	worldTexture.m_srcRect.w = static_cast<int>(cameraBox.w());
	worldTexture.m_srcRect.h = static_cast<int>(cameraBox.h());

}

void PlayingState::enemysSpawnerUpdate()
{
	auto& playerBox(m_player->getComponent<BoxComponent>());
	if (static_cast<unsigned int>(m_entityManager.getEntitiesByGroup(GEnemy).size() < m_maxEnemies))
	{
		if (m_enemySpawnTimer >= m_enemySpawnTimerMax)
		{
			// Spawn the enemy adn reset the timer
			spawnEnemy(playerBox.m_pPosComp->m_position, 400.f);
			m_enemySpawnTimer = 0.0f;
		}
		else
		{
			m_enemySpawnTimer += 1.0f;
		}
	}
}

Entity& PlayingState::createWorld(const Vector2f& rPosition, const Vector2f& rSize, const std::string& textureName)
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<PositionComponent>(rPosition);
	entity.addComponent<BoxComponent>(rSize);
	entity.addComponent<SpriteComponent>(m_pGame->getRenderer(), textureName);
	entity.addComponent<TransformComponent>();
	entity.addGroup(PlayingStateGroup::GWorld);

	return (entity);
}

Entity& PlayingState::createPlayer(const Vector2f& rPosition, const Vector2f& rSize, const std::string& textureName)
{
	auto& entity(m_entityManager.addEntity());
	entity.addComponent<PositionComponent>(rPosition);
	entity.addComponent<BoxComponent>(rSize);
	entity.addComponent<SpriteComponent>(m_pGame->getRenderer(), textureName);
	
	entity.addComponent<TransformComponent>();
	entity.addComponent<KeyboardMovementComponent>(Vector2f{0.2f, 0.2f});
	auto& keyboard(entity.getComponent<KeyboardMovementComponent>());
	keyboard.m_worldSize = m_worldSize;
	entity.addComponent<AnimationComponent>();
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
	entity.addComponent<SpriteComponent>(m_pGame->getRenderer(), "mob_5.png");
	entity.addComponent<EnemyAIComponent>();
	
	entity.addComponent<PhysicsComponent>();
	auto& physics(entity.getComponent<PhysicsComponent>());
	physics.m_velocity = { 0.1f, 0.1f };
	physics.m_worldSize = m_worldSize;

	entity.addGroup(PlayingStateGroup::GEnemy);
	return (entity);
}

Entity& PlayingState::createCamera(const Vector2f& rPosition, const Vector2f& rSize)
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<PositionComponent>(Vector2f{ m_pGame->getWinWidth() / 2.0f, m_pGame->getWinHeigth() / 2.0f });
	
	entity.addComponent<BoxComponent>(m_pGame->getWinSize());
	entity.addComponent<TransformComponent>();

	entity.addGroup(PlayingStateGroup::GCamera);
	return (entity);
}

Entity& PlayingState::createBullet(const Vector2f& rPosition, const Vector2f& rSize, const float& angleDir, const std::string& textureName)
{
	auto& entity(m_entityManager.addEntity());
	entity.addComponent<PositionComponent>(rPosition);
	entity.addComponent<BoxComponent>(rSize);

	entity.addComponent<SpriteComponent>(m_pGame->getRenderer(), textureName);
	auto& sprite(entity.getComponent<SpriteComponent>());
	sprite.m_angle = angleDir;

	entity.addComponent<PhysicsComponent>();
	auto& physics(entity.getComponent<PhysicsComponent>());
	physics.m_velocity = {0.5f, 0.5f};
	physics.m_worldSize = m_worldSize;

	entity.addGroup(PlayingStateGroup::GBullet);
	return (entity);
}

void PlayingState::spawnEnemy(const Vector2f& playerPos, const float& minDistanceToThePlayer)
{
	Vector2f pos{ 0.0f, 0.0f };
	
	switch (RandomGenerator::getRandomInt(1, 4))
	{
		// right
		case 1:
			pos.x = RandomGenerator::getRandomFloat(playerPos.x + minDistanceToThePlayer, m_worldSize.x);
			pos.y = playerPos.y;
			break;
		// left
		case 2:
			pos.x = RandomGenerator::getRandomFloat(playerPos.x - minDistanceToThePlayer, 0);
			pos.y = playerPos.y;
			break;
		// bottom
		case 3:
			pos.x = playerPos.x;
			pos.y = RandomGenerator::getRandomFloat(playerPos.y + minDistanceToThePlayer, m_worldSize.y);
			break;
		// top
		case 4:
			pos.x = playerPos.x;
			pos.y = RandomGenerator::getRandomFloat(playerPos.y - minDistanceToThePlayer, 0);
			break;
		
		default:
			break;
	}

	createEnemy(pos, {32.0f, 32.0f});
}

void PlayingState::fire()
{
	auto& bullets(m_entityManager.getEntitiesByGroup(GBullet));
	if (bullets.size() >= m_numAmmo)
	{
		bullets.at(0)->destroy();
	}

	auto& playerSprite(m_player->getComponent<SpriteComponent>());
	auto& playerPos(m_player->getComponent<PositionComponent>());

	Vector2f pos = playerPos.m_position;
	std::string textureName = { "bullet.png" };
	Vector2f size = ResourceHolder::get().textures.getTextureSize(textureName);
	float angle = playerSprite.m_angle;

	createBullet(pos, size, angle, textureName);
}