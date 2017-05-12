#ifndef INCLUDED_DISPLAY
#define INCLUDED_DISPLAY

#include "Path.h"

namespace Display
{
	void MoveCursorToLocation(Coord location);

	//Displays a given character or string at a given coordinate within the console.
	void ShowCharAtLocation(std::string symbol, Coord location);

	//Erases any character at the given coordinate within the console.
	void HideCharAtLocation(Coord location);

	//Show or hide the cursor
	void SetCursorVisibility(bool visible);
}

#endif
