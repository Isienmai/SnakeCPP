#ifndef INCLUDED_GAMEBASE
#define INCLUDED_GAMEBASE

#include <time.h>
#include <fstream>
#include <string>

class GameBase
{
	//This value si the size of the time gap between snake movements.
	int ARBITRARY_TIMER;
	//Values which determine if the game is running, and if the arena has walls.
	bool gameRunning, walls;
	//Stores the size of the grid
	Coord gridSize;

public:
	GameBase();
	//Initialises ARBITRARY_TIMER(int), walls(bool), and gridSize from the config file.
	void ReadConfigFile();
	~GameBase();
	//The main game loop, call this to run the game itself.
	void GameLoop();
};

#endif

