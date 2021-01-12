#include "Engine.h"
#include "Logger.h"
#include "Input.h"
#include "SDL/SDL_keycode.h"

Engine* Engine::instance = nullptr;

void Engine::Run()
{
	Logger::Log("Init game");
	// Init

	instance = this;

	m_window = new Window("Game", 1280, 720);

	// Running

	m_running = true;

	while (m_running)
	{
		Input::Update();
		m_window->Update();

		if (Input::KeyboardCheck('a'))
		{
			Logger::Log("A held");
		}
		if (Input::KeyboardCheckPressed('b'))
		{
			Logger::Log("B pressed");
		}
		if (Input::KeyboardCheckReleased('c'))
		{
			Logger::Log("C released");
		}
		if (Input::KeyboardCheckPressedRepeat('d'))
		{
			Logger::Log("D pressed repeat");
		}
	}

	// End

	delete m_window;
}

void Engine::Quit()
{
	Logger::Log("Quitting");
	m_running = false;
}

Engine* Engine::Get()
{
	return instance;
}
