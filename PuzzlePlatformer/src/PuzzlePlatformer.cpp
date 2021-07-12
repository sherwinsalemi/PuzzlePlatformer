#include <iostream>
#include "Engine.h"
#include "Logger.h"
#include "Input.h"
#include "Math.h"
#include "SDL/SDL_keycode.h"

class DebugObject : public Object
{
	float mesh[28] = 
	{
		0.5f, 0.5f, 1.0f, 0.501f, 0.737f, 0.911f, 1.0f,
		0.5f,-0.5f, 1.0f, 0.086f, 1.000f, 0.521f, 1.0f,
	   -0.5f,-0.5f, 1.0f, 0.086f, 1.000f, 0.521f, 1.0f,
	   -0.5f, 0.5f, 1.0f, 0.501f, 0.737f, 0.911f, 1.0f,
	};
	uint32_t meshIndex[6] = 
	{
		0, 1, 2,
		2, 3, 0
	};

	VertexBuffer vbo;
	IndexBuffer ibo;

	void Create()
	{
		vbo = CreateVertexBuffer(mesh, sizeof(mesh));
		ibo = CreateIndexBuffer(meshIndex, sizeof(meshIndex) / sizeof(uint32_t));

		Logger::Log("DebugObj Created");
	}
	void Update()
	{
		// Logger::Log("DebugObj Updated");

		if (Input::KeyboardCheck(SDLK_x))
		{
			Logger::Log("DebugObj Destroyed");
			Engine::Get()->GetObjectSystem()->RemoveObject(this);
		}
	}
	void Render()
	{
		Engine::Get()->GetRender()->Draw(&vbo, &ibo);
	}
	void Destroy()
	{
	}
};

int main()
{
	Matrix4 a;
	Matrix4 b;

	float matrixA[16] = { 1, 5, 3, 4, 7, 6, 5, 4, 8, 1, 2, 3, 1, 4, 5, 7 };
	float matrixB[16] = { 1, 4, 2, 3, 5, 6, 9, 8, 9, 9, 0, 7, 8, 6, 4, 5 }; 

	memcpy(a.data, matrixA, sizeof(matrixA));
	memcpy(b.data, matrixB, sizeof(matrixB));

	Matrix4 finalMat = MultiplyMatrix(a, b);

	for (int i = 0; i < 16; i++)
	{
		Logger::Log(std::to_string(finalMat.data[i]));
	}

	Engine engine;

	engine.Init();

	DebugObject object;

	engine.GetObjectSystem()->AddObject(&object);

	engine.Run();

	return 0;
}