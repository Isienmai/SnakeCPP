#include "stdafx.h"


Snake::Snake()
{
	points = Path();
	snakeLength = 0;
	//Add three points on initialisation so that the player has something to control.
	AddSegment(Coord(3, 4));
	AddSegment(Coord(4, 4));
	AddSegment(Coord(5, 4));
	currentDirection = Coord(1, 0);
	nextDirection = Coord(1, 0);
	lastInput = 2;
}


Snake::~Snake()
{
}

void Snake::Move()
{
	AddSegment(Coord(points.Start()->point + currentDirection));	
}

Coord Snake::GetTargetLocation()
{
	//Return the coordinate that the head will occupy if it travels in the current direction.
	currentDirection = nextDirection;
	return Coord(points.Start()->point + currentDirection);
}

void Snake::ResetLastInput()
{
	lastInput = 0;
}

void Snake::UpdateDirection(int input)
{
	//If the current input is the same as the last input then nothing needs to be done
	if (input != lastInput)
	{
		//Modify input(int) such that only NEW button presses are present.
		input = ~lastInput & input;
		//Set inputTransformation(Coord) to be the opposite of current direction so that if input is not one of the four directions nextDirection is not modified.
		Coord inputTransformation = Coord(0, 0) - currentDirection;

		//Modify inputTransformation(coord) to be one of the four directional transformations based on the input direction.
		switch (input)
		{
		case 1:
			inputTransformation = Coord(0, -1);
			break;
		case 2:
			inputTransformation = Coord(1, 0);
			break;
		case 4:
			inputTransformation = Coord(0, 1);
			break;
		case 8:
			inputTransformation = Coord(-1, 0);
			break;
		}

		if (inputTransformation + currentDirection != Coord(0, 0))
		{
			nextDirection = inputTransformation;
		}

		//Update lastInput(int).
		lastInput = input;
	}	
}

bool Snake::CollidingWithSelf(Coord newHead)
{
	//Loop through the snake to see if the given Coordinate is already present.
	if (!points.IsEmpty())
	{
		PathNode* temp = points.Start();
		while (temp != nullptr)
		{
			if (temp->point == newHead)
			{
				return true;
			}
			temp = temp->next;
		}
	}
	return false;
}

void Snake::Draw()
{
	PathNode* temp = points.Start();
	while (temp != nullptr)
	{
		Display::ShowCharAtLocation("O", temp->point + Coord(1, 1));
		temp = temp->next;
	}
}

bool Snake::KeepHeadWithinBounds(Coord bounds, bool walls)
{
	if (points.Start()->point.x > bounds.x - 1)
	{
		if (walls) return false;
		points.Start()->point.x -= bounds.x;
	}
	if (points.Start()->point.x < 0)
	{
		if (walls) return false;
		points.Start()->point.x += bounds.x;
	}
	if (points.Start()->point.y > bounds.y - 1)
	{
		if (walls) return false;
		points.Start()->point.y -= bounds.y;
	}
	if (points.Start()->point.y < 0)
	{
		if (walls) return false;
		points.Start()->point.y += bounds.y;
	}

	return true;
}

void Snake::AddSegment(Coord segment)
{
	points.AddFirst(segment);
	snakeLength++;
}

Coord Snake::RemoveTail()
{	
	snakeLength--;
	return points.CutLast();
}