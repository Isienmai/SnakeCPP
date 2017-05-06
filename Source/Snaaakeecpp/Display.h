#ifndef INCLUDED_DISPLAY
#define INCLUDED_DISPLAY

#include <string>
#include "Path.h"

namespace Display
{
	//Displays a given character or string at a given coordinate within the console.
	void ShowCharAtLocation(std::string symbol, Coord location);
	
	//Erases any character at the given coordinate within the console.
	void HideCharAtLocation(Coord location);
}

#endif
