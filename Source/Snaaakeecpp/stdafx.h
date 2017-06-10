// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef INCLUDED_STDAFX
#define INCLUDED_STDAFX

#include <iostream>

#include <fstream>
#include <string>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#ifdef WIN32
#include "targetver.h"
#include <windows.h> 
#endif

#ifdef __linux
#include <fcntl.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#endif


#endif
