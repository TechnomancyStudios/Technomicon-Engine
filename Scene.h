#pragma once
#include "GameObject.h"
#include "Sprite.h"
/*
	Scene should contain:
	Object Manager
	Player
	Objects
	Background Layers
	Music
*/
const int MAX_BACKGROUNDS = 5;

class Scene
{
public:
	std::string sceneName = "";

	GameObjectManager* gameObjectManager;

	Background backgrounds[MAX_BACKGROUNDS];

	Scene(std::string sceneName) { this->sceneName = sceneName; gameObjectManager = new GameObjectManager(); }
	~Scene() { delete gameObjectManager; };

	void Update();
	void Render();
	void LoadBackground(Sprite* background, int index);

private:

};

