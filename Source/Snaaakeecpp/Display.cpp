#include "stdafx.h"


void Display::ShowCharAtLocation(std::string symb, Coord loca)
{
	//Move the cursor to the given coordinate and then output the given string.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {loca.x, loca.y});
	std::cout << symb;
}

void Display::HideCharAtLocation(Coord loca)
{
	//Move the cursor to the given coordinate and then output a space.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { loca.x, loca.y });
	std::cout << " ";
}