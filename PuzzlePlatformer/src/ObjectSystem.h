#pragma once

#include <vector>

class Object
{
public:
	virtual void Create() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
};

class ObjectSystem
{
public:
	ObjectSystem();

	void AddObject(Object* object);
	void RemoveObject(Object* object);

	void UpdateObjects();
	void RenderObjects();
private:
	std::vector<Object*> objects;
};