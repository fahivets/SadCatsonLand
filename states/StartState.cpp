#include "stdafx.h"
#include "StartState.h"
#include "PlayingState.h"
#include "../MainGame.h"

StartState::StartState(MainGame& game) : State(game)
{
	initStateResources();
	createStateEntitys();
	playMusic();
}

StartState::~StartState()
{
}

void StartState::endState()
{
	ResourceHolder::get().audio.stopMusic();
}

void StartState::handleInput(const InputManager& input)
{
	if (input.keyDown(SDL_SCANCODE_Q))
	{
		needPop(true);
	}
	if (input.keyDown(SDL_SCANCODE_RETURN))
	{
		m_pGame->pushState<PlayingState>(*m_pGame);
	}
	m_entityManager.handleInput(input);
}

void StartState::update(const float& deltaTime)
{
	m_entityManager.refresh();
	m_entityManager.update(deltaTime);
}

void StartState::render(SDL_Renderer& rRender)
{
	m_entityManager.render(rRender);
}

// Private functions
void StartState::initStateResources()
{
	// Load textures
	ResourceHolder::get().textures.set(m_pGame->getRenderer(), "sad_cat.png");

	// Load audio
	ResourceHolder::get().audio.setMusic("opening_theme.mp3");
	ResourceHolder::get().audio.setSound("meow.ogg");
}

void StartState::createStateEntitys()
{
	createAllButtons();

	createBackground({ m_pGame->getWinSize().x / 2.0f, m_pGame->getWinSize().y * 0.3f },
		ResourceHolder::get().textures.getTextureSize("sad_cat.png"));

}

void StartState::playMusic()
{
	ResourceHolder::get().audio.playMusic("opening_theme.mp3");
}

void StartState::createAllButtons()
{
	// Start Button Param
	ButtonTextureArray startButtonTextures{
		ResourceHolder::get().fonts.getText(m_pGame->getRenderer(), "Start Game", "basic.ttf", 42, {200, 200, 200}),
		ResourceHolder::get().fonts.getText(m_pGame->getRenderer(), "Start Game", "basic.ttf", 41, {200, 100, 0}),
		ResourceHolder::get().fonts.getText(m_pGame->getRenderer(), "Start Game", "basic.ttf", 43, {200, 0, 0})
	};
	Vector2f startButtonPos = { m_pGame->getWinSize().x / 2, m_pGame->getWinSize().y * 0.7f };
	Vector2f startButtonSize = ResourceHolder::get().textures.queryTexture(startButtonTextures[0]);
	std::function<void(void)> startButtonFunc = [&]() -> void
	{
		ResourceHolder::get().audio.playSound("meow.ogg", 0, 0, 42);
		ResourceHolder::get().audio.stopMusic();
		m_pGame->pushState<PlayingState>(*m_pGame);
	};

	// Options Button Param
	ButtonTextureArray optionsButtonTextures{
		ResourceHolder::get().fonts.getText(m_pGame->getRenderer(), "Settings", "basic.ttf", 42, {200, 200, 200}),
		ResourceHolder::get().fonts.getText(m_pGame->getRenderer(), "Settings", "basic.ttf", 41, {200, 100, 0}),
		ResourceHolder::get().fonts.getText(m_pGame->getRenderer(), "Settings", "basic.ttf", 43, {200, 0, 0})
	};
	Vector2f optionsButtonPos = { m_pGame->getWinSize().x / 2, m_pGame->getWinSize().y * 0.8f };
	Vector2f optionsButtonSize = ResourceHolder::get().textures.queryTexture(optionsButtonTextures[0]);
	std::function<void(void)> optionsButtonFunc = [&]() -> void
	{
		ResourceHolder::get().audio.playSound("meow.ogg", 0, 0, 42);
		std::cout << "Settings in progress ^_^" << "\n";
	};

	// Exit Button Param
	ButtonTextureArray exitButtonTextures{
		ResourceHolder::get().fonts.getText(m_pGame->getRenderer(), "Exit", "basic.ttf", 42, {200, 200, 200}),
		ResourceHolder::get().fonts.getText(m_pGame->getRenderer(), "Exit", "basic.ttf", 41, {200, 100, 0}),
		ResourceHolder::get().fonts.getText(m_pGame->getRenderer(), "Exit", "basic.ttf", 43, {200, 0, 0})
	};
	Vector2f exitButtonPos = { m_pGame->getWinSize().x / 2, m_pGame->getWinSize().y * 0.9f };
	Vector2f exitButtonSize = ResourceHolder::get().textures.queryTexture(exitButtonTextures[0]);
	std::function<void(void)> exitButtonFunc = [&]() -> void
	{
		needPop(true);
	};

	createButton(startButtonPos, startButtonSize, startButtonTextures,startButtonFunc);
	createButton(optionsButtonPos, optionsButtonSize, optionsButtonTextures, optionsButtonFunc);
	createButton(exitButtonPos, exitButtonSize, exitButtonTextures, exitButtonFunc);
}

Entity& StartState::createButton(const Vector2f& rPosition, const Vector2f& rSize, const ButtonTextureArray& buttonTextures, std::function<void(void)> function)
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<PositionComponent>(rPosition);
	entity.addComponent<BoxComponent>(rSize);
	entity.addComponent<UIButtonComponent>(buttonTextures);
	auto& button(entity.getComponent<UIButtonComponent>());
	button.setFunction(function);

	entity.addGroup(StartStateGroup::GButton);
	return (entity);
}
Entity& StartState::createBackground(const Vector2f& rPosition, const Vector2f& rSize)
{
	auto& entity(m_entityManager.addEntity());

	entity.addComponent<PositionComponent>(rPosition);
	entity.addComponent<BoxComponent>(Vector2f{ rSize.x, rSize.y });
	entity.addComponent<SpriteComponent>(m_pGame->getRenderer(), "sad_cat.png");
	entity.addGroup(StartStateGroup::GBackground);

	return (entity);
}