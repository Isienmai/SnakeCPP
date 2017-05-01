#ifndef INCLUDED_GRID
#define INCLUDED_GRID

class Grid
{
	//Store the bery's location and the size of the grid.
	Coord berry, gridSize;
	//A pointer to the snake.
	Snake *snake;
	//Is true if the are walls, if false then the snake cannot die from wall collisions.
	bool walls;

	//Displays the berry.
	void DrawBerry();
	
public:
	Grid(bool _walls, Coord _GridSize);
	~Grid();
	//Updates the snake's intended next direction based on the last input.
	void UpdateSnake(int input);
	//Moves the snake based on its intended next direction and reacts accordingly to berry, snake and wall collisions.
	bool MoveSnake();
	//Puts the berry at a random location on the board not currently occupied by the snake.
	bool MoveBerry();
	//Draw's the berry and the snake.
	void DrawContent();
	//Draw's the board itself.
	void DrawOutline();

	Coord GridSize() { return gridSize; }
	int Score() { return snake->SnakeLength(); }
};

#endif

