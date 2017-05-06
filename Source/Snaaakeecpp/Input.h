#ifndef INCLUDED_INPUT
#define INCLUDED_INPUT

namespace Input
{
	//Returns an int based on what directional keys are currently held down.
	int GetInputNonBlocking();
	int GetInputBlocking();
}

#endif
