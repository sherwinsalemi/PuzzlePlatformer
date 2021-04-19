#include "Engine.h"
#include "Logger.h"
#include "Input.h"
#include "SDL/SDL_keycode.h"

Engine* Engine::instance = nullptr;

void Engine::Init()
{
	Logger::Log("Init game");
	// Init

	instance = this;

	m_window = new Window("Game", 1280, 720);
	m_render = new Render(m_window->GetNativeWindow());
	m_objectSystem = new ObjectSystem();
}

void Engine::Run()
{
	// Running
	m_running = true;

	while (m_running)
	{
		// update
		Input::Update();
		m_window->Update();

		if (Input::KeyboardCheck(SDLK_ESCAPE))
		{
			m_running = false;
		}

		m_objectSystem->UpdateObjects();

		// render

		m_render->Clear();

		m_render->RenderTest();

		m_objectSystem->RenderObjects();

		m_render->SwapBuffers();
	}

	// End
	delete m_render;
	delete m_window;
	delete m_objectSystem;
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

Render* Engine::GetRender()
{
	return m_render;
}

ObjectSystem* Engine::GetObjectSystem()
{
	return m_objectSystem;
}
