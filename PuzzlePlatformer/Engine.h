#pragma once
#include "Window.h"
#include "Render.h"

class Engine
{
public: 
	void Run();
	void Quit();
	static Engine* Get();
	
private:
	bool m_running;
	Window* m_window;
	Render* m_render;
	static Engine* instance;
};