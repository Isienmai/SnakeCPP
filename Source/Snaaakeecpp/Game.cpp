#include "stdafx.h"


GameBase::GameBase()
{			
	ReadConfigFile();
}

void GameBase::ReadConfigFile()
{
	std::string infoDump;
	std::ifstream readStream("config.txt");
	int gridX = 20, gridY = 20;

	//Move through the file by dumping text into infoDump, them put the value into ARBITRARY_TIMER(int).
	readStream >> infoDump;
	readStream >> infoDump;
	readStream >> ARBITRARY_TIMER;

	//Move through the file by dumping text into infoDump, them put the value into walls(bool).
	readStream >> infoDump;
	readStream >> infoDump;
	readStream >> infoDump;
	readStream >> walls;

	readStream >> infoDump;
	readStream >> infoDump;
	readStream >> gridX;
	readStream >> infoDump;
	readStream >> gridY;

	readStream.close();

	//If the ARBITRARY_TIMER(int) value is out of bounds (0-100) move it back into bounds.
	bool valueIncorrect = false;
	if (ARBITRARY_TIMER > 100)
	{
		valueIncorrect = true;
		ARBITRARY_TIMER = 100;
	}
	if (ARBITRARY_TIMER < 0)
	{
		valueIncorrect = true;
		ARBITRARY_TIMER = 0;
	}

	//Prevent the board's width from being greater than that of the console window.
	if (gridX > 78)
	{
		valueIncorrect = true;
		gridX = 78;
	}
	if (gridY > 50)
	{
		valueIncorrect = true;
		gridY = 50;
	}
	if (gridX < 10)
	{
		valueIncorrect = true;
		gridX = 10;
	}
	if (gridY < 10)
	{
		valueIncorrect = true;
		gridY = 10;
	}

	//If the ARBITRARY_TIMER(int) value was out of bounds, re-write the config file such that the contained value is within bounds.
	if (valueIncorrect)
	{
		std::ofstream writeStream("config.txt");
		writeStream << "Snake speed: " << ARBITRARY_TIMER << "\n";
		writeStream << "Collide with walls: " << walls << "\n";
		writeStream << "Grid Dimensions: " << gridX << " , " << gridY << "\n";
		writeStream.close();
	}

	//Invert the ARBITRARY_TIMER(int) value, such that a high config speed results in a low maximum timer value.
	ARBITRARY_TIMER = 100 - ARBITRARY_TIMER;
	gridSize = Coord(gridX, gridY);
}

GameBase::~GameBase()
{	
}

void GameBase::GameLoop()
{
	//Clock is used to force the snake to move slow enough to control.
	clock_t lastTime = clock();

	Grid theGrid = Grid(walls, gridSize);
	bool victory = false;
	theGrid.DrawOutline();
	gameRunning = true;

	//while the game is not over, run the game.
	while (gameRunning)
	{
		//Update the snakes input/direction every tick for smooth controls.
		theGrid.UpdateSnake(Input::GetInput());
		//Only update the snake's movement and the screens display once every X milliseconds to keep the snake at a manageable speed.
		if (clock() - lastTime > ARBITRARY_TIMER)
		{
			lastTime = clock();
			//If the snakes motion results in a collision, gamerunning is set to false;
			gameRunning = theGrid.MoveSnake();
			if (gameRunning) theGrid.DrawContent();
		}
		
		//If the snake completely fills the board then the player has won.
		if (theGrid.Score() == (theGrid.GridSize().y * theGrid.GridSize().x))
		{
			victory = true;
			gameRunning = false;
		}
	}

	//display victory or defeat+score message.
	if (victory)
	{
		Display::ShowCharAtLocation("-Victory!", Coord(1, theGrid.GridSize().y + 2));
	}
	else
	{
		Display::ShowCharAtLocation("-Defeat! Score:" + std::to_string(theGrid.Score()), Coord(1, theGrid.GridSize().y + 2));
	}		

	//Wait for user input before exiting.
	std::cin.ignore();
}
