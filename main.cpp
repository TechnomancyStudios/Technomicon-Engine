#include "Engine.h"
#undef main

int main()
{
	Engine::Init("YEET", 1280, 720);

	Engine::Update();

	return 0;
}