#pragma once

struct SDL_Window;
typedef void* SDL_GLContext;

class Render
{
public:
	Render(SDL_Window* window);
	~Render();
	void SwapBuffers();
	void RenderTest();
private:
	SDL_Window* m_window;
	SDL_GLContext m_context;
};