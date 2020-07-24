#ifndef STATE_H_INCLUDE
#define STATE_H_INCLUDE
#include "utility/NonCopyable.h"

class MainGame;
class InputManager;

class State : public NonCopyable
{
public:
	// Constructors/Destructors
	State(MainGame& game);
	virtual ~State();

	// Set 
	void needPop(bool status);
	// Get
	const bool& checkForQuit() const;

	// Virtual functions
	virtual void endState() = 0;
	virtual void handleInput(const InputManager& input) = 0;
	virtual void update(const float& deltaTime) = 0;
	virtual void render(SDL_Renderer& render) = 0;
	
protected:
	MainGame* m_pGame;

private:
	bool m_needPop;
};

#endif	/*	end STATE_H_INCLUDE	*/