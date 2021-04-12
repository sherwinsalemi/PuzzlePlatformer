#include <iostream>
#include "Engine.h"

#ifdef NDEBUG
#include <Windows.h>
#endif

int main()
{
#ifdef NDEBUG
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

	Engine engine;

	engine.Init();

	engine.Run();

	return 0;
}