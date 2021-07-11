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
	Matrix4 mat = IdentityMatrix();
	Matrix4 transform;

	transform.data[0] = 1.0f;
	transform.data[4] = 1.0f;
	transform.data[8] = 1.0f;
	transform.data[12] = 1.0f;

	Matrix4 finalMat = MultiplyMatrix(transform, mat);

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