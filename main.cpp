#include "Engine.h"
#undef main

int main()
{
	Engine::Init("Suits: Absolute Power", 1280, 720);

	Engine::Update();

	return 0;
}