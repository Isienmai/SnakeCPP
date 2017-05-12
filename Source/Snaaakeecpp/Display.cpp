#include "stdafx.h"
#include "Display.h"

void Display::MoveCursorToLocation(Coord loca)
{
	//Move the cursor differently depending on platform
#ifdef WIN32
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (SHORT)loca.x, (SHORT)loca.y });
#endif
#ifdef __LINUX__
	std::cout << "\033[" << loca.y << ";" << loca.x << "H";
#endif
}

void Display::ShowCharAtLocation(std::string symb, Coord loca)
{
	Display::MoveCursorToLocation(loca);
	std::cout << symb;
}

void Display::HideCharAtLocation(Coord loca)
{
	Display::MoveCursorToLocation(loca);
	std::cout << " ";
}

void Display::SetCursorVisibility(bool visible)
{
#ifdef WIN32
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = visible;
	cursorInfo.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
#endif

#ifdef __LINUX__
	if(visible)
	{
		//Showcursor
		std::cout << "\e[?25h";
	}
	else
	{
		//Hide cursor
		std::cout << "\e[?25l";
	}
#endif
}
