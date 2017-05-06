// Snaaakeecpp.cpp : Defines the entry point for the console application.
//

#include "Game.h"

#include <iostream>

//Initialise and run the game
int main(int argc, char* argv[])
{
	#ifdef __linux
	//Save cursor position and switch to the alternate console
	std::cout << "\0337\033[?47h\033[2J";
	#endif

	GameBase coreGame;

	coreGame.GameLoop();

	#ifdef __linux
	//Clear alternat console, switch back to original console, restore cursor
	std::cout << "\033[2J\033[?47l\0338";
	#endif

	return 0;
}
