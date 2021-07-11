#include "Render.h"
#include "Logger.h"

#include <SDL/SDL.h>
#include <glad/glad.h>
#include <string>
#include <math.h>

Render::Render(SDL_Window* window)
{
	m_window = window;
	m_context = SDL_GL_CreateContext(m_window);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		Logger::Error("Failed to initialize OpenGL Context");
		exit(1);
	}

	uint32_t VAOId;
	glGenVertexArrays(1, &VAOId);
	glBindVertexArray(VAOId);


	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec4 aColor;\n"
		"out vec4 vertexColor;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"   vertexColor = aColor;"
		"}";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec4 vertexColor;\n"
		//"uniform float ourColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(vertexColor.x, vertexColor.y, vertexColor.z, vertexColor.a);\n"
		"}";


	// shader program creation

	m_shaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

	BindShaderProgram(&m_shaderProgram);
}

Render::~Render()
{
}

void Render::SwapBuffers()
{
	SDL_GL_SwapWindow(m_window);
}

void Render::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Render::Draw(VertexBuffer* vbo, IndexBuffer* ibo)
{
	BindIndexBuffer(ibo);

	{
		BindVertexBuffer(vbo);
		glEnableVertexAttribArray(0); // vertex pos
		glEnableVertexAttribArray(1); // color
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(sizeof(float) * 3));
	}

	glDrawElements(GL_TRIANGLES, ibo->count, GL_UNSIGNED_INT, 0);
}

void Render::RenderTest()
{
	// shader data
	//Uint32 timeValue = SDL_GetTicks();
	//float colorValue = (sinf(timeValue/150.0f) / 2.0f) + 0.5f;
	//int ourColorLocation = glGetUniformLocation(m_shaderProgram.shaderID, "ourColor");

	//glUniform1f(ourColorLocation, colorValue);

	
	// vertex buffer and element buffer creation

	float verticies[] = {
		-0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f
	};

	uint32_t indicies[] = {
		0, 1, 2
	};

	// float texCoords[] = {
	// 	0.0f, 0.0f,
	// 	1.0f, 0.0f,
	// 	0.5f, 1.0f
	// };

	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//unsigned int VBO;
	VertexBuffer VBO = CreateVertexBuffer(verticies, sizeof(verticies));
	IndexBuffer IBO = CreateIndexBuffer(indicies, sizeof(verticies)/sizeof(uint32_t));

	
	BindIndexBuffer(&IBO);

	{
		BindVertexBuffer(&VBO);
		glEnableVertexAttribArray(0); // vertex pos
		glEnableVertexAttribArray(1); // color
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(sizeof(float)*3));
	}

	glDrawElements(GL_TRIANGLES, IBO.count, GL_UNSIGNED_INT, 0);
}

ShaderProgram CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	// shader setup
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// shader error checking

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		Logger::Error("Error compiling shader: " + std::string(infoLog));
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		Logger::Error("Error compiling shader: " + std::string(infoLog));
	}

	// shader program creation

	ShaderProgram shaderProgram;

	shaderProgram.shaderID = glCreateProgram();

	glAttachShader(shaderProgram.shaderID, vertexShader);
	glAttachShader(shaderProgram.shaderID, fragmentShader);
	glLinkProgram(shaderProgram.shaderID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGetProgramiv(shaderProgram.shaderID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram.shaderID, 512, NULL, infoLog);
		Logger::Error("Error linking shader program: " + std::string(infoLog));
	}

	return shaderProgram;
}

void BindShaderProgram(ShaderProgram* shaderProgram)
{
	glUseProgram(shaderProgram->shaderID);
}

void DeleteShaderProgram(ShaderProgram* shaderProgram)
{
	glDeleteProgram(shaderProgram->shaderID);
}



VertexBuffer CreateVertexBuffer(float points[], size_t size)
{
	VertexBuffer buffer;
	buffer.size = size;

	glGenBuffers(1, &buffer.bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, buffer.bufferID);
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

	return buffer;
}

void BindVertexBuffer(VertexBuffer* buffer) 
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer->bufferID);
}

void DeleteVertexBuffer(VertexBuffer* buffer)
{
	glDeleteBuffers(1, &buffer->bufferID);
}



IndexBuffer CreateIndexBuffer(unsigned int indices[], size_t count)
{
	IndexBuffer buffer;
	buffer.count = count;

	glGenBuffers(1, &buffer.bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

	return buffer;
}

void BindIndexBuffer(IndexBuffer* buffer)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->bufferID);
}

void DeleteIndexBuffer(IndexBuffer* buffer)
{
	glDeleteBuffers(1, &buffer->bufferID);
}
