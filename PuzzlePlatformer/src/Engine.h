#pragma once
#include "Window.h"
#include "Render.h"
#include "ObjectSystem.h"

class Engine
{
public: 
	void Init();
	void Run();
	void Quit();
	static Engine* Get();
private:
	bool m_running;
	Window* m_window;
	Render* m_render;
	ObjectSystem* m_objectSystem;
	static Engine* instance;
};