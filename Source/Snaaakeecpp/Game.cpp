#include "stdafx.h"
#include "Game.h"
#include "Input.h"
#include "Display.h"

GameBase::GameBase()
{
	//Setup default config values
	timeDelayPerFrame = 10;
	walls = 1;

	ReadConfigFile();

	theGrid = new Grid(walls, gridSize);
	victory = false;
	gameRunning = true;
}

GameBase::~GameBase()
{
	delete(theGrid);
}

void GameBase::ReadConfigFile()
{
	std::string infoDump;
	std::ifstream readStream("config.txt");
	int gridX = 20, gridY = 20;

	//TODO: Replace the following with text parsing

	//store if any of the config file values were out of bounds. Assume not by default.
	bool valueIncorrect = true;
	if(readStream.is_open())
	{
		valueIncorrect = false;

		//Move through the file by dumping text into infoDump, them put the value into timeDelayPerFrame.
		readStream >> infoDump;
		readStream >> infoDump;
		readStream >> timeDelayPerFrame;

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

		//If the timeDelayPerFrame(int) value is out of bounds (0-100) move it back into bounds.
		if (timeDelayPerFrame > 100)
		{
			valueIncorrect = true;
			timeDelayPerFrame = 100;
		}
		if (timeDelayPerFrame < 0)
		{
			valueIncorrect = true;
			timeDelayPerFrame = 0;
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
	}
	else
	{
		#ifdef __linux
		creat("config.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		#endif
	}


	//If any of the config values were out of bounds modify the text file to bring them back within bounds
	if (valueIncorrect)
	{
		std::ofstream writeStream("config.txt");
		writeStream << "Snake speed: " << timeDelayPerFrame << "\n";
		writeStream << "Collide with walls: " << walls << "\n";
		writeStream << "Grid Dimensions: " << gridX << " , " << gridY << "\n";
		writeStream.close();
	}

	//Invert the timeDelayPerFrame value, such that a high config speed results in a low maximum timer value.
	timeDelayPerFrame = 100 - timeDelayPerFrame;
	gridSize = Coord(gridX, gridY);
}

void GameBase::GameLoop()
{
	theGrid->DrawOutline();

#ifdef WIN32
	clock_t *lastTime = new clock_t();
	clock_t *currentTime = new clock_t();

	*lastTime = clock();
#endif

#ifdef __linux
	//Clock is used to force the snake to move slow enough to control.
	timespec *lastTime = new timespec();
	timespec *currentTime = new timespec();

	clock_gettime(CLOCK_MONOTONIC, lastTime);
#endif
	//while the game is not over, run the game.
	while (gameRunning)
	{
#ifdef WIN32
        *currentTime = clock();
        Tick((*currentTime - *lastTime));
#endif

#ifdef __linux
		clock_gettime(CLOCK_MONOTONIC, currentTime);
		Tick((currentTime->tv_nsec - lastTime->tv_nsec)/1000000.0f);
#endif
		*lastTime = *currentTime;
	}

	//display victory or defeat message.
	if (victory)
	{
		Display::ShowCharAtLocation("-Victory!", Coord(1, theGrid->GetGridSize().y + 2));
	}
	else
	{
		Display::ShowCharAtLocation("-Defeat! Score:" + std::to_string(theGrid->GetScore()), Coord(1, theGrid->GetGridSize().y + 2));
	}

	Display::ShowCharAtLocation("Press any key and then hit ENTER to exit the game.", Coord(1, theGrid->GetGridSize().y + 3));

	delete(lastTime);
	delete(currentTime);

	//Wait for user input before exiting.
	Input::GetInputBlocking();
}


void GameBase::Tick(float deltaTime)
{
	timeSinceLastFrame += deltaTime;
	if(timeSinceLastFrame < 0.0f) timeSinceLastFrame = 0.0f;

	theGrid->UpdateSnake(Input::GetInputNonBlocking());

	if (timeSinceLastFrame > (float)timeDelayPerFrame)
	{
			timeSinceLastFrame = 0.0f;

			//If the snake cannot move the game ends
			gameRunning = theGrid->MoveSnake();
			theGrid->DrawContent();
	}

	//If the snake completely fills the board then the player has won.
	if(theGrid->GetScore() == (theGrid->GetGridSize().y * theGrid->GetGridSize().x))
	{
			victory = true;
			gameRunning = false;
	}
}
