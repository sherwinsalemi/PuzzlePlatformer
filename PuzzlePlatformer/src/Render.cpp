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

	VertexArrayObject VAO;

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	VAO.Bind();

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
							      	 "}";

	const char* fragmentShaderSource = "#version 330 core\n"
		                               "out vec4 FragColor;\n"
									   "in vec4 vertexColor;\n"
									   "uniform float ourColor;\n"
		                               "void main()\n"
		                               "{\n"
		                               "  FragColor = vec4(vertexColor.x, vertexColor.y, ourColor, vertexColor.a);\n"
		                               "}";
	

	// shader program creation

	ShaderProgram shaderProgram = ShaderProgram(vertexShaderSource, fragmentShaderSource);


	/*
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	GLint success = false;
	char infoLog[513]{};
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		Logger::Error("Error linking shader program: " + std::string(infoLog));
	}*/

	// shader uniform setting

	Uint32 timeValue = SDL_GetTicks();
	float colorValue = (sinf(timeValue/150.0f) / 2.0f) + 0.5f;
	int ourColorLocation = glGetUniformLocation(shaderProgram.shaderID, "ourColor");

	shaderProgram.Bind();

	glUniform1f(ourColorLocation, colorValue);

	
	// vertex buffer and element buffer creation

	float verticies[] = {
		-0.5f, -0.5f, 1.0f,
		-0.5f, 0.5f, 1.0f,
		0.5f, -0.5f, 1.0f,
		0.5f, 0.5f, 1.0f
	};

	unsigned int indicies[] = {
		0, 1, 2,
		1, 3, 2
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
	VertexBuffer VBO = VertexBuffer(verticies, sizeof(verticies));
	IndexBuffer EBO = IndexBuffer(indicies, sizeof(indicies) / sizeof(uint32_t));

	
	EBO.Bind();

	{
		VBO.Bind();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	}

	glDrawElements(GL_TRIANGLES, EBO.GetCount(), GL_UNSIGNED_INT, 0);
}

VertexBuffer::VertexBuffer(float points[], size_t size)
{
	glGenBuffers(1, &this->bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, this->bufferID);
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &this->bufferID);
}

unsigned int VertexBuffer::GetId()
{
	return this->bufferID;
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->bufferID);
}

IndexBuffer::IndexBuffer(unsigned int indices[], size_t count)
{
	glGenBuffers(1, &this->bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	m_count = count;
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &this->bufferID);
}

unsigned int IndexBuffer::GetId()
{
	return this->bufferID;
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->bufferID);
}

size_t IndexBuffer::GetCount()
{
	return m_count;
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

	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	glLinkProgram(shaderID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
		Logger::Error("Error linking shader program: " + std::string(infoLog));
	}
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(shaderID);
}

void ShaderProgram::Bind()
{
	glUseProgram(shaderID);
}