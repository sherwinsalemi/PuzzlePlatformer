#include "Window.h"
#include "SDL/SDL.h"
#include "Engine.h"

Window::Window(std::string title, int width, int height)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
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
		}
	}
}
