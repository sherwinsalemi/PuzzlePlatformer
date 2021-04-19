#include "Window.h"
#include "SDL/SDL.h"
#include "Engine.h"
#include "Logger.h"
#include <string>
#include "Input.h"

Window::Window(std::string title, int width, int height)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
}

Window::~Window()
{
	SDL_DestroyWindow(m_window);

	SDL_Quit();
}

void Window::Update()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			Engine::Get()->Quit();
			break;
		case SDL_KEYDOWN:
			if (e.key.repeat == 0)
			{
				Input::SetKeyDown(e.key.keysym.sym);
			}
			else
			{
				Input::SetKeyDownRepeat(e.key.keysym.sym);
			}
			//Logger::Log(std::to_string((int)e.key.keysym.sym) + " pressed");
			break;
		case SDL_KEYUP:
			Input::SetKeyUp(e.key.keysym.sym);
			//Logger::Log(std::to_string((int)e.key.keysym.sym) + " released");
			break;
		}
	}
}

SDL_Window* Window::GetNativeWindow()
{
	return m_window;
}
