#include "GameObject.h"
#include "Engine.h"

void GameObject::Update()
{

}

void GameObject::Render()
{

}

void GameObject::OnCollide(GameObject* object)
{

}

void GameObject::OnMouseEnter(Mouse* mouse)
{

}

void GameObject::OnMouseLeave(Mouse* mouse)
{

}

GameObject::GameObject()
{
	Engine::gameManager->AddObject(this);
}

bool CheckCollision(GameObject& one, GameObject& two)
{
	bool obj1_exist = (&one != nullptr);
	bool obj2_exist = (&two != nullptr);

	if (obj1_exist && obj2_exist)
	{
		bool xAxisCol = ((one.collision.colXY1.x - one.collision.origin.x) + one.collision.colXY2.x >= (two.collision.colXY1.x - two.collision.origin.x)) && ((two.collision.colXY1.x - two.collision.origin.x) + two.collision.colXY2.x >= (one.collision.colXY1.x - one.collision.origin.x));
		bool yAxisCol = ((one.collision.colXY1.y - one.collision.origin.y) + one.collision.colXY2.y >= (two.collision.colXY1.y - two.collision.origin.y)) && ((two.collision.colXY1.y - two.collision.origin.y) + two.collision.colXY2.y >= (one.collision.colXY1.y - one.collision.origin.y));

		return (xAxisCol && yAxisCol);
	}
	else
		return 0;
}

bool CheckMouseEnter(GameObject& one, Mouse* mouse)
{
	bool obj1_exist = (&one != nullptr);

	if (obj1_exist)
	{
		bool xAxisCol = ( (one.collision.colXY1.x - one.collision.origin.x) + one.collision.colXY2.x >= (mouse->worldPosition.x) ) && ( mouse->worldPosition.x >= (one.collision.colXY1.x - one.collision.origin.x) );
		bool yAxisCol = ((one.collision.colXY1.y - one.collision.origin.y) + one.collision.colXY2.y >= (mouse->worldPosition.y)) && (mouse->worldPosition.y >= (one.collision.colXY1.y - one.collision.origin.y));

		return (xAxisCol && yAxisCol);
	}
	else
		return 0;
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

	for (unsigned int i = 0; i < mSize; i++)
	{
		for (unsigned int j = 0; j < mSize; j++)
		{
			if (CheckCollision(*objects[i], *objects[j]))
			{
				if (objects[i] != objects[j])
				{
					if (objects[i] != nullptr)
					{
						objects[i]->OnCollide(objects[j]);
					}
				}
			}

			if (CheckMouseEnter(*objects[i], mouse))
			{
				if (objects[i] != nullptr)
				{
					objects[i]->OnMouseEnter(mouse);
				}
			}
			else
			{
				if (objects[i] != nullptr)
				{
					objects[i]->OnMouseLeave(mouse);
				}
			}
		}
	}
}

void GameObjectManager::Render()
{
	for (unsigned int i = 0; i < mSize; i++)
	{
		objects[i]->Render();
	}
}