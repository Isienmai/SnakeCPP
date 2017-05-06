#include "Input.h"

#include <iostream>

int Input::GetInputNonBlocking()
{
	//If a given key is pressed then a unique bit of the returned integer is set.
	int toReturn = 0b0000;


///	if (GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP))
///	{
///		toReturn |= 0b0001;
///	}
///	if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT))
///	{
///		toReturn |= 0b0010;
///	}
///	if (GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN))
///	{
///		toReturn |= 0b0100;
///	}
///	if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT))
///	{
///		toReturn |= 0b1000;
///	}


	return toReturn;
}

int Input::GetInputBlocking()
{
	int toReturn;

	std::cin >> toReturn;

	return toReturn;
}
