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
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	bool m_status;
	Vector2f m_winSize;
	int m_winWidth;
	int m_winHeigth;
	// Init Private Functions
	void initVariables();
	bool initSDL();
	bool initWindow(const int& width, const int& heigth);
	bool initRenderer();
	void quit();
};

#endif	/*	end DISPLAYMANAGER_H_INCLUDE	*/
