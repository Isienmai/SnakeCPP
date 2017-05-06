// Snaaakeecpp.cpp : Defines the entry point for the console application.
//

#include "Game.h"

#include <iostream>

//Initialise and run the game
int main(int argc, char* argv[])
{
	//Setup the console
	//TODO: Replace with proper console setup
	#ifdef __linux
	std::system("clear");
	#endif

	GameBase coreGame;

	coreGame.GameLoop();

	return 0;
}
