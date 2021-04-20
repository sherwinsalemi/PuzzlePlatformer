#pragma once

#include <cstddef>

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

class VertexBufferObject
{
public:
	VertexBufferObject(float points[], size_t size);
	~VertexBufferObject();
	unsigned int GetId();
	void Bind();
private:
	unsigned int bufferID;
};

class ElementBufferObject
{
public:
	ElementBufferObject(unsigned int indicies[], size_t count);
	~ElementBufferObject();
	unsigned int GetId();
	void Bind();
	size_t GetCount();
private:
	size_t m_count;
	unsigned int bufferID;
};

class VertexArrayObject
{
public:
	VertexArrayObject();
	~VertexArrayObject();
	void Bind();
private:
	unsigned int arrayID;
};

class ShaderProgram
{
public:
	ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
	~ShaderProgram();
	void Bind();
public:
	unsigned int shaderID;
};