// Snaaakeecpp.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Game.h"
#include "Display.h"


//Switch to an alternate console and hide the cursor
void InitialiseConsole()
{
#ifdef __linux
	//Save cursor position and switch to the alternate console
	std::cout << "\0337\033[?47h\033[2J";

	//De-activate cursor
	Display::SetCursorVisibility(false);
#endif
}

//Switch back to the original console and re-enable the cursor
void DestroyConsole()
{
#ifdef __linux
	//Clear alternat console, switch back to original console, restore cursor
	std::cout << "\033[2J\033[?47l\0338";

	//Undo changes made in the Input class
	struct termios oldt;
	tcgetattr(STDIN_FILENO, &oldt);
	oldt.c_lflag |= ICANON | ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl (STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) & (~O_NONBLOCK));

	//Re-activate cursor
	Display::SetCursorVisibility(true);
#endif
}

void CtrlcHandler(int s)
{
	DestroyConsole();
	exit(1);
}

//Initialise and run the game
int main(int argc, char* argv[])
{
#ifdef __linux
	//Setup the Ctrl C Handler
	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = CtrlcHandler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	sigaction(SIGINT, &sigIntHandler, NULL);

	InitialiseConsole();
#endif
	GameBase coreGame;

	coreGame.GameLoop();

	DestroyConsole();

	return 0;
}
