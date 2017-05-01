#include "stdafx.h"

int Input::GetInput()
{
	//If a given key is pressed then a unique bit of the returned integer is set.
	int toReturn = 0;
	if (GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP))
	{
		toReturn += 1;
	}
	if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT))
	{
		toReturn += 2;
	}
	if (GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN))
	{
		toReturn += 4;
	}
	if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT))
	{
		toReturn += 8;
	}
	return toReturn;
}