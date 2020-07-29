#ifndef DISPLAYMANAGER_H_INCLUDE
#define DISPLAYMANAGER_H_INCLUDE
#include "utility/NonCopyable.h"
#include "utility/NonMovable.h"

class DisplayManager : public NonCopyable, public NonMovable
{
public:
	// Constructors/Destructors
	DisplayManager();
	~DisplayManager();

	// Functions
	void initDisplayManager(const int& width = WINDOW_DEFAULT::WIDTH, const int& heigth = WINDOW_DEFAULT::HEIGTH);

	SDL_Window& getWindow() const;
	SDL_Renderer& getRenderer() const;
	const bool& getStatus() const;
	const int& getWinWidth() const;
	const int& getWinHeigth() const;
	const Vector2f& getWinSize() const;

private:
	// Init Private Functions
	void initVariables();
	bool initSDL();
	bool initWindow(const int& width, const int& heigth);
	bool initRenderer();
	void quit();

private:
	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };
	bool m_status{ false };
	Vector2f m_winSize{ 0.0f, 0.0f };
	int m_winWidth{ 0 };
	int m_winHeigth{ 0 };
};

#endif	/*	end DISPLAYMANAGER_H_INCLUDE	*/
