#include "Scene.h"

void Scene::Update()
{
	gameObjectManager->Update();
}

void Scene::Render(SDL_Renderer* render)
{
	for (auto b : backgrounds)
		b.Render(render);

	gameObjectManager->Render(render);
}

void Scene::LoadBackground(Sprite* background, int index)
{
	if (index < MAX_BACKGROUNDS && index >= 0)
	{
		backgrounds[index].sprite = background;
	}
}

