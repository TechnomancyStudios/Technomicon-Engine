#include "Player.h"

//Sprite test(0, 0, 215, 265, 0, 0, 0);

Player::Player()
{
	sprite = new Sprite();
}

Player::Player(GameObjectManager* gameObjectManager)
{
	gm = gameObjectManager;
	gm->AddObject(this);
	sprite = new Sprite();
}

void Player::Init(int x, int y)
{
	this->x = x;
	this->y = y;
	sprite = new Sprite();
}

void Player::Update()
{

}

void Player::Render(SDL_Renderer* renderer)
{
	//sprite->Render(renderer);
}
