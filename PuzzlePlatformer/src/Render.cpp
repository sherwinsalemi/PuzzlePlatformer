#include "Render.h"
#include "Logger.h"

#include <SDL/SDL.h>
#include <glad/glad.h>
#include <string>

Render::Render(SDL_Window* window)
{
	m_window = window;
	m_context = SDL_GL_CreateContext(m_window);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		Logger::Error("Failed to initialize OpenGL Context");
		exit(1);
	}

	// loaded opengl successfully

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

void Render::RenderTest()
{
	const char* vertexShaderSource = "#version 330 core\n"
									 "layout (location = 0) in vec3 aPos;\n"
									 "void main()\n"
									 "{\n"
									 "	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
							      	 "}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		                               "out vec4 FragColor;\n"
		                               "void main()\n"
		                               "{\n"
		                               "  FragColor = vec4(1.0f, 0.0f, 0.0f, 1.f);\n"
		                               "}\0";

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

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

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		Logger::Error("Error linking shader program: " + std::string(infoLog));
	}

	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float verticies[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	unsigned int VBO;
	unsigned int VAO;
	glGenBuffers(1, &VBO);

	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	
	glDrawArrays(GL_TRIANGLES, 0, 3);
}