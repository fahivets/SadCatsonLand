#include "stdafx.h"
#include "DisplayManager.h"

DisplayManager::DisplayManager()
{
	initVariables();	
}

DisplayManager::~DisplayManager()
{
	quit();
}

void DisplayManager::initDisplayManager(const int& width, const int& heigth)
{
	if (getStatus())
		return;
	m_winHeigth = width;
	m_winWidth = heigth;
	m_winSize = { static_cast<float>(width), static_cast<float>(heigth) };
	if (initSDL() && initWindow(width, heigth) && initRenderer())
	{
		//SDL_ShowCursor(0);
		m_status = true;
	}
	else
	{
		std::cerr << "[SDL_ERROR] " << SDL_GetError() << std::endl;
	}
}

SDL_Window& DisplayManager::getWindow() const
{
	return (*m_window);
}

SDL_Renderer& DisplayManager::getRenderer() const
{
	return (*m_renderer);
}

const bool& DisplayManager::getStatus() const
{
	return (m_status);
}

const int& DisplayManager::getWinWidth() const
{
	return (m_winWidth);
}

const int& DisplayManager::getWinHeigth() const
{
	return (m_winHeigth);
}

const Vector2f& DisplayManager::getWinSize() const
{
	return(m_winSize);
}

void DisplayManager::initVariables()
{
	m_status = false;
	m_window = nullptr;
	m_renderer = nullptr;
}

bool DisplayManager::initSDL()
{
	return ((SDL_Init(SDL_INIT_EVERYTHING) == 0) ? (true) : (false));
}

bool DisplayManager::initWindow(const int& width, const int& heigth)
{
	m_window = SDL_CreateWindow(":SAD_CATSONLAND:",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, heigth,
		0);

	return ((m_window == nullptr) ? (false) : (true));
}

bool DisplayManager::initRenderer()
{
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	// Get current window size
	int winWidth{ 0 };
	int winHeigth{ 0 };
	SDL_GetWindowSize(m_window, &winWidth, &winHeigth);

	if (m_renderer)
	{
		SDL_RenderSetLogicalSize(m_renderer, winWidth, winHeigth);
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
		return (true);
	}
	else
		return (false);
}

void DisplayManager::quit()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
	m_window = nullptr;
	m_renderer = nullptr;
	m_status = false;
}
