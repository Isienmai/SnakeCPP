#include "Path.h"

Coord Coord::operator+ (const Coord &other) const
{
	return Coord(this->x + other.x, this->y + other.y);
}

Coord Coord::operator- (const Coord &other) const
{
	return Coord(this->x - other.x, this->y - other.y);
}

bool Coord::operator== (const Coord &other) const
{
	if (this->x != other.x)
	{
		return false;
	}
	if (this->y != other.y)
	{
		return false;
	}
	return true;
}

bool Coord::operator!= (const Coord &other) const
{
	if (this->x != other.x)
	{
		return true;
	}
	if (this->y != other.y)
	{
		return true;
	}
	return false;
}

Path::~Path()
{
	while (start != nullptr)
	{
		CutFirst();
	}
}

void Path::AddLast(Coord toAdd)
{
	if (start != nullptr)
	{
		PathNode* temp = start;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = new PathNode(toAdd, nullptr);
	}
	else
	{
		start = new PathNode(toAdd, nullptr);
	}
}

void Path::AddFirst(Coord toAdd)
{
	start = new PathNode(toAdd, start);
}

Coord Path::CutLast()
{
	Coord toReturn;
	if (start != nullptr)
	{
		if (start->next == nullptr)
		{
			toReturn = start->point;
			delete start;
			start = nullptr;
		}
		else
		{
			PathNode* temp = start;
			while (temp->next->next != nullptr)
			{
				temp = temp->next;
			}
			toReturn = temp->next->point;
			delete temp->next;
			temp->next = nullptr;
		}
	}
	return toReturn;
}

Coord Path::CutFirst()
{
	Coord toReturn;
	if (start != nullptr)
	{
		toReturn = start->point;
		PathNode* temp = start;
		start = start->next;
		delete temp;
	}
	return toReturn;
}

bool Path::IsEmpty()
{
	if (start == nullptr)
	{
		return true;
	}
	return false;
}

bool Path::ContainsDuplicate()
{
	//Loops through the entire list twice, one loop selects the value to check against, the second loop checks all following values against the value to be checked against.
	//If there is a duplicate value within the list then return true;
	if (!IsEmpty())
	{
		PathNode toCheck = *start, *nextToCheck = start->next, *toCheckAgainst;

		while (nextToCheck != nullptr)
		{
			toCheckAgainst = nextToCheck;
			while (toCheckAgainst != nullptr)
			{
				if (toCheckAgainst->point == toCheck.point)
				{
					return true;
				}
				toCheckAgainst = toCheckAgainst->next;
			}
			toCheck = *nextToCheck;
			nextToCheck = toCheck.next;
		}
	}
	return false;
}
