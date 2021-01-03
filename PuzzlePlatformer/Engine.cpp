#include "Engine.h"
#include "Logger.h"

Engine* Engine::instance = nullptr;

void Engine::Run()
{
	Logger::Log("Init");
	Logger::Warn("Init");
	Logger::Error("Init");
	// Init

	instance = this;

	m_window = new Window("Game", 1280, 720);

	// Running

	m_running = true;

	while (m_running)
	{
		m_window->Update();
	}

	// End

	delete m_window;
}

void Engine::Quit()
{
	m_running = false;
}

Engine* Engine::Get()
{
	return instance;
}
