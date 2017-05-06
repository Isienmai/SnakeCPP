#ifndef INCLUDED_GAMEBASE
#define INCLUDED_GAMEBASE

#include "Grid.h"

class GameBase
{
public:
	GameBase();

	~GameBase();

	//The main game loop, call this to run the game itself.
	void GameLoop();

private:
	//This value dictates the game's tick frequency.
	int timeDelayPerFrame;
	//Store the time since the last frame was drawn
	float timeSinceLastFrame;

	//Store if the game is currently running
	bool gameRunning;
	//Store if the game was won
	bool victory;

	//true if the snake arena should wrap
	bool walls;

	//Stores the size of the grid
	Coord gridSize;

	//Grid holding the snake and berries
	Grid* theGrid;

	//Initialises ARBITRARY_TIMER, walls, and gridSize from the config file.
	void ReadConfigFile();

	//Execute every tick, passing in the time since the previous tick.
	void Tick(float deltaTime);
};

#endif
