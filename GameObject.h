#pragma once
#include <array>
#include <iostream>
#include <SDL.h>

const unsigned int MAX_OBJECTS = 5000;
class GameObject;
class GameObjectManager;

class GameObject
{
public:
	unsigned int id = 0;
	virtual void Update();
	virtual void Render(SDL_Renderer* renderer);
	GameObjectManager* gm;
	GameObject();
	GameObject(GameObjectManager* gameObjectManager);
};

class GameObjectManager
{
public:
	SDL_Renderer* renderer;
	void AddObject(GameObject* obj);
	void RemoveObject(GameObject* obj);
	void Update();
	void Render(SDL_Renderer* renderer);
private:
	std::array<GameObject*, MAX_OBJECTS>objects;
	unsigned int mSize = 0;
};






