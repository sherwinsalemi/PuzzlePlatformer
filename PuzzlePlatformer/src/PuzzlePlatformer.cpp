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
	Vector4 b;

	float matrixA[16] = { 1, 5, 3, 4, 7, 6, 5, 4, 8, 1, 2, 3, 1, 4, 5, 7 };

	memcpy(a.data, matrixA, sizeof(matrixA));

	b.x = 3;
	b.y = 7;
	b.z = 5;
	b.w = 2;

	Vector4 c = TransformVector(a, b);

	Logger::Log(std::to_string(c.x));
	Logger::Log(std::to_string(c.y));
	Logger::Log(std::to_string(c.z));
	Logger::Log(std::to_string(c.w));

	Engine engine;

	engine.Init();

	DebugObject object;

	engine.GetObjectSystem()->AddObject(&object);

	engine.Run();

	return 0;
}