#ifndef INPUTMANAGER_H_INCLUDE
#define INPUTMANAGER_H_INCLUDE
#include "utility/NonCopyable.h"
#include "utility/NonMovable.h"
enum MOUSE_BUTTONS
{
	LEFT = 0,
	RIGHT,
	MIDDLE,
	BACK,
	FORWARD
};

class InputManager : public NonCopyable, public NonMovable
{
public:

	// Constructor/Destructor
	InputManager();
	~InputManager();

	// Keyboard Functions
	bool keyDown(SDL_Scancode scancode) const;
	bool keyPressed(SDL_Scancode scancode) const;
	bool keyReleased(SDL_Scancode scancode) const;

	// Mouse Functions
	bool mouseButtonDown(MOUSE_BUTTONS mouseButton) const;
	bool mouseButtonPressed(MOUSE_BUTTONS mouseButton) const;
	bool mouseButtonReleased(MOUSE_BUTTONS mouseButton) const;
	Vector2f mousePos() const;

	// Functions
	void update();
	void updatePrevInput();

private:
	// Keyboard variables
	const Uint8* m_keyboardState{ nullptr };
	Uint8* m_prevKeyboardState{ nullptr };
	int m_keysArrayLen;

	// Mouse variables
	Uint32 m_mouseState;
	Uint32 m_prevMouseState;
	int m_mouseXPos;
	int m_mouseYPos;
};

#endif	/*	end INPUTMANAGER_H_INCLUDE	*/
