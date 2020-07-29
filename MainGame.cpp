#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
	m_display.initDisplayManager(800, 600);

	if (m_display.getStatus())
	{
		if (initResource())
		{
			m_isRunning = true;
			pushState<StartState>(*this);
		}
	}
	else
	{
		std::cerr << "[GAME_INIT_ERROR]" << std::endl;
	}
}

MainGame::~MainGame()
{
	m_isRunning = false;
	// Remove all states here
	while (!m_states.empty())
	{
		m_states.pop();
	}
}

bool MainGame::isRunning() const
{
	return (m_isRunning);
}

void MainGame::update(const float& deltaTime)
{
	m_states.top()->update(deltaTime);
}

void MainGame::handleInput()
{
	m_input.update();

	while (SDL_PollEvent(&m_event))
	{
		if (m_event.type == SDL_QUIT)
		{
			m_isRunning = false;
		}
	}
	// Update states input here
	m_states.top()->handleInput(m_input);
}

void MainGame::render()
{
	SDL_RenderClear(&m_display.getRenderer());

	m_states.top()->render(m_display.getRenderer());

	SDL_RenderPresent(&m_display.getRenderer());
}

void MainGame::run()
{
	float deltaTime{ 0.0f };
	float lag{ 0.0f };

	//Game loop		
	while (isRunning() && !m_states.empty())
	{
		// Handle Input
		handleInput();

		lag += deltaTime;
		while (lag >= constFTimeSlice)
		{
			// Update
			update(constFTimeStep);
		
			// Update prev input
			m_input.updatePrevInput();

			lag -= constFTimeSlice;
		}

		// Render
		render();

		// Update states status and pop it
		updateState();

		// Update delta time every frame
		deltaTime = m_timer.getDelta();
		/* show FPS
		// TPM Update Window Title
		std::string title = "FT: " + std::to_string(deltaTime) + "\t FPS : " + std::to_string(m_timer.getFPS(deltaTime));
		SDL_SetWindowTitle(&m_display.getWindow(), title.c_str());
		*/
	}
}

void MainGame::updateState()
{
	if (m_states.top()->checkForQuit())
	{
		m_states.top()->endState();
		m_states.pop();
	}
}

// DisplayManager geters
SDL_Window& MainGame::getWindow() const
{
	return (m_display.getWindow());
}

const int& MainGame::getWinWidth() const
{
	return (m_display.getWinWidth());
}

const int& MainGame::getWinHeigth() const
{
	return (m_display.getWinHeigth());
}

const Vector2f& MainGame::getWinSize() const
{
	return (m_display.getWinSize());
}

SDL_Renderer& MainGame::getRenderer() const
{
	return (m_display.getRenderer());
}

// States functions
void MainGame::pushState(std::unique_ptr<State> state)
{
	m_states.push(std::move(state));
}

State& MainGame::getCurrentState()
{
	return (*m_states.top());
}

bool MainGame::initResource()
{
	ResourceHolder::get().textures.init(m_display.getRenderer());
	ResourceHolder::get().fonts.init();
	ResourceHolder::get().audio.init();

	if (ResourceHolder::get().textures.getStatus()
		&& ResourceHolder::get().audio.getStatus()
		&& ResourceHolder::get().audio.getStatus())
	{
		return (true);
	}
	return false;
}
