#pragma once
#include "GameObject.h"
#include "Sprite.h"

class Player : public GameObject
{
public:
	int x, y;

	Sprite* sprite;

	void Init(int x, int y);
	void Update();
	void Render(SDL_Renderer* renderer);

	Player();
	Player(GameObjectManager* gameObjectManager);
};
