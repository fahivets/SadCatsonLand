#include "stdafx.h"
#include "MainGame.h"

int main(int argc, char** argv)
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	MainGame game;

	game.run();

	std::cout << "<<< QUIT_GAME >>>" << std::endl;
	return (0);
}