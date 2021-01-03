#pragma once
#include "Window.h"

class Engine
{
public: 
	void Run();
	void Quit();
	static Engine* Get();
	
private:
	bool m_running;
	Window* m_window;
	static Engine* instance;
};