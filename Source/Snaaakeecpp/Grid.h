#ifndef INCLUDED_GRID
#define INCLUDED_GRID

#include "Path.h"
#include "Snake.h"

class Grid
{
public:

	Grid(bool _walls, Coord _GridSize);

	~Grid();

	//Updates the snake's intended next direction based on the last input.
	void UpdateSnake(int input);
	//Moves the snake based on its intended next direction and reacts accordingly to berry, snake and wall collisions.
	bool MoveSnake();
	//Puts the berry at a random location on the board not currently occupied by the snake.
	bool MoveBerry();

	//Draws the berry and the snake.
	void DrawContent();
	//Draws the board itself.
	void DrawOutline();

	Coord GetGridSize() { return gridSize; }
	int GetScore() { return snake->SnakeLength(); }

private:
	//Store the berry's location
	Coord berry;
	//Store the grid size
	Coord gridSize;

	//A pointer to the snake.
	Snake *snake;

	//if false then the snake cannot die from wall collisions.
	bool walls;

	void DrawBerry();
};

#endif
