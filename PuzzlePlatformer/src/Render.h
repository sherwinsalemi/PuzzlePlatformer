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
	void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
private:
	SDL_Window* m_window;
	SDL_GLContext m_context;
};