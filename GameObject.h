#pragma once
#include <array>
#include <iostream>
#include <SDL.h>
#include "Collision2D.h"
#include "Input.h"

const unsigned int MAX_OBJECTS = 5000;
class GameObject;
class GameObjectManager;

bool CheckCollision(GameObject& one, GameObject& two);
bool CheckMouseEnter(GameObject& one, Mouse* mouse);


class GameObject
{
public:
	Collision2D collision;
	unsigned int id = 0;
	glm::vec2 position;
	virtual void Update();
	virtual void Render();
	virtual void OnCollide(GameObject* object);
	virtual void OnMouseEnter(Mouse* mouse);
	virtual void OnMouseLeave(Mouse* mouse);
	GameObject();
};

class GameObjectManager
{
public:
	SDL_Renderer* renderer;
	Mouse* mouse;
	void AddObject(GameObject* obj);
	void RemoveObject(GameObject* obj);

	void Update();
	void Render();
private:
	std::array<GameObject*, MAX_OBJECTS>objects;
	unsigned int mSize = 0;
};






