#include "Scene.h"

void Scene::Update()
{
	gameObjectManager->Update();
}

void Scene::Render()
{
	for (auto b : backgrounds)
		b.Render();

	gameObjectManager->Render();
}

void Scene::LoadBackground(Sprite* background, int index)
{
	if (index < MAX_BACKGROUNDS && index >= 0)
	{
		backgrounds[index].sprite = background;
	}
}

