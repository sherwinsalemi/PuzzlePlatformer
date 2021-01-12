#include "Render.h"

#include <SDL/SDL.h>

Render::Render(SDL_Window* window)
{
	m_window = window;
	m_context = SDL_GL_CreateContext(m_window);
}

Render::~Render()
{
}

void Render::SwapBuffers()
{
	
	SDL_GL_SwapWindow(m_window);
}
