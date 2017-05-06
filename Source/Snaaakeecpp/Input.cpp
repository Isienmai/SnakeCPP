#include "Input.h"

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int Input::GetInputNonBlocking()
{
	//If a given key is pressed then a unique bit of the returned integer is set.
	int toReturn = 0b0000;

#ifdef __linux
	//Store the olf and new termios structs
	struct termios oldt, newt;
	//store the old fcntl data
	int oldf;

	//Get the current termios data
	tcgetattr(STDIN_FILENO, &oldt);

	//Set the current termios to not echo and to deactivate canon mode
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	//Get the current fcntl data
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

	//set fctnl to not block
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	//Get the last character
	int ch = getchar();
	//Get input controls from received character
	switch(ch)
	{
		case 'w':
			toReturn |= 0b0001;
			break;
		case 'd':
			toReturn |= 0b0010;
			break;
		case 's':
			toReturn |= 0b0100;
			break;
		case 'a':
			toReturn |= 0b1000;
			break;
	}

	//undo all changes to the termios and fcntl
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	//Return the character to the list
	if(ch != EOF)
	{
		//TODO: Figure out why this line crashes the game
		//ungetc(ch, stdin);
	}
#endif

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
	fcntl (0, F_SETFL, fcntl(0, F_GETFL, 0) & (~O_NONBLOCK));
	int toReturn;

	std::cin >> toReturn;

	return toReturn;
}
