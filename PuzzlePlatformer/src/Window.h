#pragma once
#include <string>

struct SDL_Window; 

class Window
{
public:
	Window(std::string title, int width, int height);
	~Window();
	void Update();
	SDL_Window* GetNativeWindow();
private:
	SDL_Window* m_window;
};