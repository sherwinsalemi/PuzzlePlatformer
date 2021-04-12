#include "ObjectSystem.h"

ObjectSystem::ObjectSystem()
{
	
}

void ObjectSystem::AddObject(Object* object)
{
	objects.push_back(object);
	object->Create();
}

void ObjectSystem::RemoveObject(Object* object)
{
	object->Destroy();
	std::vector<Object*>::iterator position = std::find(objects.begin(), objects.end(), object);
	if (position != objects.end())
	{
		// Object was found, erase it
		objects.erase(position);
	}
}

void ObjectSystem::UpdateObjects()
{
	for (Object* i : objects)
	{
		i->Update();
	}
}

void ObjectSystem::RenderObjects()
{
	for (Object* i : objects)
	{
		i->Render();
	}
}
