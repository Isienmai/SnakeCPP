#include "Display.h"

#include <iostream>

void Display::ShowCharAtLocation(std::string symb, Coord loca)
{
	//Move the cursor to the given coordinate and then output the given string.
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {loca.x, loca.y});
	std::cout << "\033[" << loca.y << ";" << loca.x << "H";
	std::cout << symb;
}

void Display::HideCharAtLocation(Coord loca)
{
	//Move the cursor to the given coordinate and then output a space.
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { loca.x, loca.y });
	std::cout << "\033[" << loca.y << ";" << loca.x << "H";
	std::cout << " ";
}

void Display::SetCursorVisibility(bool visible)
{
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
}
