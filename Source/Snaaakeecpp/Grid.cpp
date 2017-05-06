#include "Grid.h"

#include "Display.h"

void Grid::DrawBerry()
{
	Display::ShowCharAtLocation("Q", berry + Coord(1, 1));
}

Grid::Grid(bool _Walls, Coord _GridSize)
{
	gridSize = _GridSize;
	berry = Coord(7, 3);
	snake = new Snake();
	walls = _Walls;
	MoveBerry();
}

Grid::~Grid()
{
	delete snake;
}

void Grid::UpdateSnake(int input)
{
	//If there is no input then snake->lastInput should be reset to 0.
	if (input != 0)
	{
		snake->UpdateDirection(input);
	}
	else
	{
		snake->ResetLastInput();
	}
}

bool Grid::MoveSnake()
{
	//If the snake would collide with itself then don't move it and return false;
	Coord targetLocation = snake->GetTargetLocation();
	if (snake->CollidingWithSelf(targetLocation))
	{
		return false;
	}

	//Move the snake and keep it within bounds BEFORE checking for berry collision, otherwise the berry collision could come up false and then the head get moved over the berry.
	snake->Move();
	if (!snake->KeepHeadWithinBounds(gridSize, walls))
	{
		snake->RemoveTail();
		return false;
	}
	else
	{
		if (snake->Head() == berry)
		{
			if (snake->SnakeLength() != (gridSize.y * gridSize.x))
			{
				MoveBerry();
			}
		}
		else
		{
			Display::HideCharAtLocation(snake->RemoveTail() + Coord(1, 1));
		}
	}
	return true;
}

bool Grid::MoveBerry()
{
	bool collision = true;
	Display::HideCharAtLocation(berry + Coord(1, 1));
	//As long as the berry is on top of the snake move the berry to a random location.
	while (collision)
	{
		collision = false;
		int random1 = rand() % (gridSize.x - 1);
		int random2 = rand() % (gridSize.y - 1);
		berry = Coord(random1 + 1, random2 + 1);

		collision = snake->CollidingWithSelf(berry);
	}

	return true;
}

void Grid::DrawContent()
{
	DrawBerry();
	snake->Draw();
}

void Grid::DrawOutline()
{
	for (int x = 0; x < gridSize.x + 1; x++)
	{
		Display::ShowCharAtLocation("#", Coord(x, 0));
		Display::ShowCharAtLocation("#", Coord(x, gridSize.y + 1));
	}

	for (int y = 0; y < gridSize.y + 1; y++)
	{
		Display::ShowCharAtLocation("#", Coord(0, y));
		Display::ShowCharAtLocation("#", Coord(gridSize.x + 1, y));
	}
	Display::ShowCharAtLocation("#", Coord(gridSize.x + 1, gridSize.y + 1));
}
