#include "stdafx.h"
#include "InputManager.h"

// Constructor/Destructor
InputManager::InputManager()
{
	m_keyboardState = SDL_GetKeyboardState(&m_keysArrayLen);
	m_prevKeyboardState = new Uint8[m_keysArrayLen];
	memcpy(m_prevKeyboardState, m_keyboardState, m_keysArrayLen);
}

InputManager::~InputManager()
{
	if (m_prevKeyboardState)
	{
		delete[] m_prevKeyboardState;
		m_prevKeyboardState = nullptr;
	}
}

// Keyboard Functions
bool InputManager::keyDown(SDL_Scancode scancode) const
{
	return (m_keyboardState[scancode]);
}

bool InputManager::keyPressed(SDL_Scancode scancode) const
{
	return (!m_prevKeyboardState[scancode] && m_keyboardState[scancode]);
}

bool InputManager::keyReleased(SDL_Scancode scancode) const
{
	return (m_prevKeyboardState[scancode] && !m_keyboardState[scancode]);
}

// Mouse Functions
bool InputManager::mouseButtonDown(MOUSE_BUTTONS mouseButton) const
{
	Uint32 mask{ 0 };

	switch (mouseButton)
	{
		case LEFT:
			mask = SDL_BUTTON_LMASK;
			break;

		case RIGHT:
			mask = SDL_BUTTON_RMASK;
			break;

		case MIDDLE:
			mask = SDL_BUTTON_MMASK;
			break;
	
		case BACK:
			mask = SDL_BUTTON_X1MASK;
			break;

		case FORWARD:
			mask = SDL_BUTTON_X2MASK;
			break;

		default:
			break;
	}

	return (m_mouseState & mask);
}

bool InputManager::mouseButtonPressed(MOUSE_BUTTONS mouseButton) const
{
	Uint32 mask{ 0 };

	switch (mouseButton)
	{
	case LEFT:
		mask = SDL_BUTTON_LMASK;
		break;

	case RIGHT:
		mask = SDL_BUTTON_RMASK;
		break;

	case MIDDLE:
		mask = SDL_BUTTON_MMASK;
		break;

	case BACK:
		mask = SDL_BUTTON_X1MASK;
		break;

	case FORWARD:
		mask = SDL_BUTTON_X2MASK;
		break;

	default:
		break;
	}

	return (!(m_prevMouseState & mask) && (m_mouseState & mask));
}

bool InputManager::mouseButtonReleased(MOUSE_BUTTONS mouseButton) const
{
	Uint32 mask{ 0 };

	switch (mouseButton)
	{
	case LEFT:
		mask = SDL_BUTTON_LMASK;
		break;

	case RIGHT:
		mask = SDL_BUTTON_RMASK;
		break;

	case MIDDLE:
		mask = SDL_BUTTON_MMASK;
		break;

	case BACK:
		mask = SDL_BUTTON_X1MASK;
		break;

	case FORWARD:
		mask = SDL_BUTTON_X2MASK;
		break;

	default:
		break;
	}

	return ((m_prevMouseState & mask) && !(m_mouseState & mask));
}

Vector2f InputManager::mousePos() const
{
	return Vector2f(static_cast<float>(m_mouseXPos), static_cast<float>(m_mouseYPos));
}

// Functions
void InputManager::update()
{
	SDL_PumpEvents();
	m_mouseState = SDL_GetMouseState(&m_mouseXPos, &m_mouseYPos);
}

void InputManager::updatePrevInput()
{
	memcpy(m_prevKeyboardState, m_keyboardState, m_keysArrayLen);
	m_prevMouseState = m_mouseState;
}
