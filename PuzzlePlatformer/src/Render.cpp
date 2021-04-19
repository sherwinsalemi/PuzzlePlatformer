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
	// shader data
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
	

	// shader program creation

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

	// shader uniform setting

	Uint32 timeValue = SDL_GetTicks();
	float colorValue = (sinf(timeValue/150.0f) / 2.0f) + 0.5f;
	int ourColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

	glUseProgram(shaderProgram);

	glUniform1f(ourColorLocation, colorValue);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// vertex buffer and element buffer creation

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

	//unsigned int VBO;
	VertexBufferObject VBO = VertexBufferObject(verticies, sizeof(verticies));
	ElementBufferObject EBO = ElementBufferObject(indicies, sizeof(indicies));
	VertexArrayObject VAO;

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	VAO.Bind();

	VBO.Bind();
	EBO.Bind();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

VertexBufferObject::VertexBufferObject(float points[], size_t size)
{
	glGenBuffers(1, &this->bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, this->bufferID);
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &this->bufferID);
}

unsigned int VertexBufferObject::GetId()
{
	return this->bufferID;
}

void VertexBufferObject::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->bufferID);
}

ElementBufferObject::ElementBufferObject(unsigned int indices[], size_t size)
{
	glGenBuffers(1, &this->bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

ElementBufferObject::~ElementBufferObject()
{
	glDeleteBuffers(1, &this->bufferID);
}

unsigned int ElementBufferObject::GetId()
{
	return this->bufferID;
}

void ElementBufferObject::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->bufferID);
}

VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &arrayID);
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &arrayID);
}

void VertexArrayObject::Bind()
{
	glBindVertexArray(arrayID);
}

ShaderProgram::ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
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

	shaderID = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		Logger::Error("Error linking shader program: " + std::string(infoLog));
	}
}

ShaderProgram::~ShaderProgram()
{

}

void ShaderProgram::Bind()
{

}