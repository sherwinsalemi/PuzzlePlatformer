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
									 "out vec4 vertexColor;\n"
									 "void main()\n"
									 "{\n"
									 "	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
									 "  vertexColor = vec4(aPos.x, aPos.y, 0.0f, 1.0f);"
							      	 "}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		                               "out vec4 FragColor;\n"
									   "in vec4 vertexColor;\n"
									   "uniform float ourColor;\n"
		                               "void main()\n"
		                               "{\n"
		                               "  FragColor = vec4(vertexColor.x, vertexColor.y, ourColor, vertexColor.a);\n"
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

	Uint32 timeValue = SDL_GetTicks();
	float colorValue = (sinf(timeValue/150.0f) / 2.0f) + 0.5f;
	int ourColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

	glUseProgram(shaderProgram);

	glUniform1f(ourColorLocation, colorValue);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	

	float verticies[] = {
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};

	unsigned int indicies[] = {
		0, 1, 2,
		0, 2, 3
	};

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}