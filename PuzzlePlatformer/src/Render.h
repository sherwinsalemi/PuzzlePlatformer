#pragma once

#include <cstddef>
#include <stdint.h>

struct SDL_Window;
typedef void* SDL_GLContext;

struct ShaderProgram
{
	unsigned int shaderID;
};

ShaderProgram CreateShaderProgram(const char* fragmentShaderSource, const char* vertexShaderSource);
void BindShaderProgram(ShaderProgram* shaderProgram);
void DeleteShaderProgram(ShaderProgram* shaderProgram);

struct VertexBuffer
{
	size_t size;
	uint32_t bufferID;
};

struct IndexBuffer
{
	size_t count;
	uint32_t bufferID;
};

VertexBuffer CreateVertexBuffer(float points[], size_t size);
void BindVertexBuffer(VertexBuffer* buffer);
void DeleteVertexBuffer(VertexBuffer* buffer);

IndexBuffer CreateIndexBuffer(unsigned int indices[], size_t count);
void BindIndexBuffer(IndexBuffer* buffer);
void DeleteIndexBuffer(IndexBuffer* buffer);

class Render
{
public:
	Render(SDL_Window* window);
	~Render();
	void SwapBuffers();
	void RenderTest();
	void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
	void Draw(VertexBuffer* vbo, IndexBuffer* ibo);
private:
	SDL_Window* m_window;
	SDL_GLContext m_context;
	ShaderProgram m_shaderProgram;
};

//class VertexArrayObject
//{
//public:
//	VertexArrayObject();
//	~VertexArrayObject();
//	void Bind();
//private:
//	unsigned int arrayID;
//};

