#ifndef INCLUDED_SNAKE
#define INCLUDED_SNAKE

#include "Path.h"

class Snake
{
private:
	//Contains the location of every segment of the snake.
	Path points;

	//Stores the direction that the snake last turned into, and the direction that the snake will turn into next as coordinate transformations.
	Coord currentDirection, nextDirection;

	//Stores the last combination of directional keys
	int lastInput;
	//the current size of the snake
	int snakeLength;

public:
	Snake();
	~Snake();

	//Adds a node ahead of the snake in the selected direction.
	void Move();

	//Returns the intended location for the snake's head to move to.
	Coord GetTargetLocation();

	//Sets lastInput(int) to zero.
	void ResetLastInput();

	//Updates nextdirection(Coord) and lastInput(int) according to the current input.
	void UpdateDirection(int input);

	//Returns true if the next snake head would collide with a previous part of the snake.
	bool CollidingWithSelf(Coord newHead);

	//Displays the snake on the console within the bounds of the board.
	void Draw();

	//Returns false if the snake's head has collided with the wall and walls are active, if walls are not active then it relocates the head to the opposite side of the board.
	bool KeepHeadWithinBounds(Coord bounds, bool walls);

	//Adds a coordinate to the front of the snake.
	void AddSegment(Coord segment);

	//Returns the coordinate of the snake's tail and then removes the tail from the snake.
	Coord RemoveTail();
	
	//Returns the coordinate of the snake's head and then removes it from the snake.
	Coord RemoveHead();

	Coord Head() { return points.Start()->point; }
	int SnakeLength() { return snakeLength; }
};

#endif
