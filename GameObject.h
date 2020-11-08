#pragma once
#include <array>
#include <iostream>
#include <SDL.h>
#include "Collision2D.h"

const unsigned int MAX_OBJECTS = 5000;
class GameObject;
class GameObjectManager;

bool CheckCollision(GameObject& one, GameObject& two);

class GameObject
{
public:
	Collision2D collision;
	unsigned int id = 0;
	virtual void Update();
	virtual void Render();
	virtual void OnCollide(GameObject* object);
	GameObject();
};

class GameObjectManager
{
public:
	SDL_Renderer* renderer;
	void AddObject(GameObject* obj);
	void RemoveObject(GameObject* obj);

	void Update();
	void Render();
private:
	std::array<GameObject*, MAX_OBJECTS>objects;
	unsigned int mSize = 0;
};






