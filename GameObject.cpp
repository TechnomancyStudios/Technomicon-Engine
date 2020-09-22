#include "GameObject.h"

void GameObject::Update()
{

}

void GameObject::Render(SDL_Renderer* renderer)
{

}

GameObject::GameObject()
{

}

GameObject::GameObject(GameObjectManager* gameObjectManager)
{
	gm = gameObjectManager;
	gm->AddObject(this);
}

void GameObjectManager::AddObject(GameObject* obj)
{
	if (mSize < MAX_OBJECTS)
	{
		objects[mSize] = obj;
		obj->id = mSize;
		mSize++;
	}
	else
	{

	}
}

void GameObjectManager::RemoveObject(GameObject* obj)
{
	if (mSize > 0)
	{
		unsigned int newPos = obj->id;
		delete objects[newPos];
		objects[newPos] = objects[mSize - 1];
		objects[newPos]->id = newPos;
		objects[mSize - 1] = nullptr;
		mSize--;
	}
	else
	{

	}
}

void GameObjectManager::Update()
{
	for (unsigned int i = 0; i < mSize; i++)
	{
		objects[i]->Update();
	}
}

void GameObjectManager::Render(SDL_Renderer* renderer)
{
	for (unsigned int i = 0; i < mSize; i++)
	{
		objects[i]->Render(renderer);
	}
}