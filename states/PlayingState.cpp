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
		auto& cameraBox(m_camera->getComponent<BoxComponent>());
		//ResourceHolder::get().audio.playSound("shotgun.wav", 0, 1);
		std::cout << "BOX_POS: " << cameraBox.m_fRect.x << " : " << cameraBox.m_fRect.y << "\n"
			<< "BOX_SIZE: " << cameraBox.m_fRect.w << " : " << cameraBox.m_fRect.h << "\n";
	}
	if (input.mouseButtonPressed(RIGHT))
	{
		auto& playerSprite(m_player->getComponent<SpriteComponent>());
		auto& playerPos(m_player->getComponent<PositionComponent>());
		auto& playerAnim(m_player->getComponent<AnimationComponent>());

		Vector2f pos = playerPos.m_position;
		std::string textureName = {"bullet.png"};
		Vector2f size = ResourceHolder::get().textures.getTextureSize(textureName);
		float angle = playerSprite.m_angle;

		Vector2f dir = playerAnim.m_viewDir; //dell

		createBullet(pos, size, dir, angle, textureName);
	}
	
	m_entityManager.handleInput(input);
}

void PlayingState::update(const float& deltaTime)
{
	m_entityManager.refresh();
	m_entityManager.update(deltaTime);

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
	if (cameraBox.x() > 1600 - cameraBox.w())
	{
		cameraBox.m_fRect.x = 1600 - cameraBox.w();
	}
	if (cameraBox.y() > 1200 - cameraBox.h())
	{
		cameraBox.m_fRect.y = 1200 - cameraBox.h();
	}
	auto& playerSprite(m_player->getComponent<SpriteComponent>());
	playerSprite.m_dstFRect.x = playerBox.x() - cameraBox.m_fRect.x;
	playerSprite.m_dstFRect.y = playerBox.y() - cameraBox.m_fRect.y;

	// fix mousepos
	auto& pAnim(m_player->getComponent<AnimationComponent>());
	pAnim.m_offset.x = cameraBox.m_fRect.x;
	pAnim.m_offset.y = cameraBox.m_fRect.y;

	auto& enemys(m_entityManager.getEntitiesByGroup(GEnemy));
	for (auto& enemy : enemys)
	{
		auto& enemyBox(enemy->getComponent<BoxComponent>());
		auto& enemySprite(enemy->getComponent<SpriteComponent>());
		auto& enemyAI(enemy->getComponent<EnemyAIComponent>());
		enemySprite.m_dstFRect.x = enemyBox.x() - cameraBox.m_fRect.x;
		enemySprite.m_dstFRect.y = enemyBox.y() - cameraBox.m_fRect.y;
		enemyAI.m_targetPos = playerBox.m_pPosComp->m_position;

		if (isIntersecting(enemyBox, playerBox))
			enemy->destroy();

	}


	auto& worldTexture(m_world->getComponent<SpriteComponent>());
//	worldTexture.m_dstFRect.x = 0;
//	worldTexture.m_dstFRect.y = 0;
	worldTexture.m_dstFRect.w = cameraBox.w();
	worldTexture.m_dstFRect.h = cameraBox.h();
	worldTexture.m_srcRect.x = static_cast<int>(cameraBox.x());
	worldTexture.m_srcRect.y = static_cast<int>(cameraBox.y());
	worldTexture.m_srcRect.w = static_cast<int>(cameraBox.w());
	worldTexture.m_srcRect.h = static_cast<int>(cameraBox.h());

	auto& bullets(m_entityManager.getEntitiesByGroup(GBullet));
	for (auto& bullet : bullets)
	{
		auto& box(bullet->getComponent<BoxComponent>());
		auto& sprite(bullet->getComponent<SpriteComponent>());
		sprite.m_dstFRect.x = box.x() - cameraBox.m_fRect.x;
		sprite.m_dstFRect.y = box.y() - cameraBox.m_fRect.y;
		for (auto& enemy : enemys)
		{
			auto& enemyBox(enemy->getComponent<BoxComponent>());
			if (isIntersecting(enemyBox, box))
			{
				enemy->destroy();
				bullet->destroy();
			}
		}
	}

	if (bullets.size() > 5)
		bullets[0]->destroy();

	if (static_cast<unsigned int>(m_entityManager.getEntitiesByGroup(GEnemy).size() < m_maxEnemies))
	{
		if (m_enemySpawnTimer >= m_enemySpawnTimerMax)
		{
			// Spawn the enemy adn reset the timer
			spawnEnemy(playerBox.m_pPosComp->m_position, 300.f);
			m_enemySpawnTimer = 0.0f;
		}
		else
			m_enemySpawnTimer += 1.0f;
	}


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
	
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "board.png");
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "bullet.png");

	// Load audio
	ResourceHolder::get().audio.setMusic("lvl_1_theme.mp3");
	ResourceHolder::get().audio.setSound("game_over.mp3");
	ResourceHolder::get().audio.setSound("stage_clear.mp3");
	ResourceHolder::get().audio.setSound("shotgun.wav");
}

void PlayingState::createStateEntitys()
{
	// Create camera
	m_camera = &createCamera();
	
	// Create wolrd
	Vector2f worldSize{1600, 1200};
	m_world = &createWorld({ 800,600 }, worldSize);

	// Create player
	Vector2f playerPos{0,0};
	Vector2f playerSize{32.0f, 32.0f};
	m_player = &createPlayer(playerPos, playerSize, "mob_5.png");

	// Create enemys
	m_maxEnemies = 10;
	m_enemySpawnTimerMax = 30.0f;
	m_enemySpawnTimer = m_enemySpawnTimerMax;
	// Updating the timer for enemy spawning
	if (static_cast<int>(m_entityManager.getEntitiesByGroup(GEnemy).size() < m_maxEnemies))
	{
		if (m_enemySpawnTimer >= m_enemySpawnTimerMax)
		{
			// Spawn the enemy adn reset the timer
			spawnEnemy(playerPos, 300.f);
			m_enemySpawnTimer = 0.0f;
		}
		else
			m_enemySpawnTimer += 1.0f;
	}

}

void PlayingState::playMusic()
{
	ResourceHolder::get().audio.playMusic("lvl_1_theme.mp3");
}

Entity& PlayingState::createWorld(const Vector2f& rPosition, const Vector2f& rSize)
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<PositionComponent>(rPosition);
	entity.addComponent<BoxComponent>(rSize);
	entity.addComponent<SpriteComponent>(m_pGame->getRenderer(), "board.png");
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
	
	entity.addGroup(PlayingStateGroup::GEnemy);
	return (entity);
}

Entity& PlayingState::createCamera()
{
	auto& entity(m_entityManager.addEntity());
	// Create camera at pos = midle of the window
	entity.addComponent<PositionComponent>(Vector2f{ m_pGame->getWinWidth() / 2.0f, m_pGame->getWinHeigth() / 2.0f });
	// 800 / 600
	entity.addComponent<BoxComponent>(m_pGame->getWinSize());
	

	entity.addGroup(PlayingStateGroup::GCamera);
	return (entity);
}

Entity& PlayingState::createBullet(const Vector2f& rPosition, const Vector2f& rSize, const Vector2f& dir, const float& angleDir, const std::string& textureName)
{
	auto& entity(m_entityManager.addEntity());
	entity.addComponent<PositionComponent>(rPosition);
	entity.addComponent<BoxComponent>(rSize);

	entity.addComponent<SpriteComponent>(m_pGame->getRenderer(), textureName);
	auto& sprite(entity.getComponent<SpriteComponent>());
	sprite.m_angle = angleDir;

	entity.addComponent<PhysicsComponent>();
	auto& physics(entity.getComponent<PhysicsComponent>());
	physics.m_dir = dir;
	//physics.m_velocity = {0.5f, 0.5f};
	physics.m_velocity = { 0.1f, 0.1f };
	entity.addGroup(PlayingStateGroup::GBullet);
	return (entity);
}

void PlayingState::spawnEnemy(const Vector2f& playerPos, const float& minDistanceToThePlayer)
{
	Vector2f pos{ 0.0f, 0.0f };
	Vector2f worldSize{ 1600, 1200 };
	
	switch (RandomGenerator::getRandomInt(1, 4))
	{
		// right
		case 1:
			pos.x = RandomGenerator::getRandomFloat(playerPos.x + minDistanceToThePlayer, worldSize.x - 50);
			pos.y = playerPos.y;
			break;
		// left
		case 2:
			pos.x = RandomGenerator::getRandomFloat(playerPos.x - minDistanceToThePlayer, 0 + 50);
			pos.y = playerPos.y;
			break;
		// bottom
		case 3:
			pos.x = playerPos.x;
			pos.y = RandomGenerator::getRandomFloat(playerPos.y + minDistanceToThePlayer, worldSize.y - 50);
			break;
		// top
		case 4:
			pos.x = playerPos.x;
			pos.y = RandomGenerator::getRandomFloat(playerPos.y - minDistanceToThePlayer, 0 + 50);
			break;
		
		default:
			break;
	}

	createEnemy(pos, {32.0f, 32.0f});
}