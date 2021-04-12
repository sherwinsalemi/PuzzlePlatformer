#include <iostream>
#include "Engine.h"
#include "Logger.h"
#include "Input.h"
#include "SDL/SDL_keycode.h"

#ifdef NDEBUG
#include <Windows.h>
#endif

class DebugObject : public Object
{
	void Create()
	{
		Logger::Log("DebugObj Created");
	}
	void Update()
	{
		Logger::Log("DebugObj Updated");

		if (Input::KeyboardCheck(SDLK_x))
		{
			Logger::Log("X");
			Engine::Get()->GetObjectSystem()->RemoveObject(this);
		}
	}
	void Render()
	{
		Logger::Log("DebugObj Rendered");
	}
	void Destroy()
	{
		Logger::Log("DebugObj Destroyed");
	}
};

int main()
{
#ifdef NDEBUG
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

	Engine engine;

	engine.Init();

	DebugObject object;

	engine.GetObjectSystem()->AddObject(&object);

	engine.Run();

	return 0;
}