// Snaaakeecpp.cpp : Defines the entry point for the console application.
//

#include "Game.h"

//Initialise and run the game
int main(int argc, char* argv[])
{
	GameBase coreGame;

	coreGame.GameLoop();

	return 0;
}
