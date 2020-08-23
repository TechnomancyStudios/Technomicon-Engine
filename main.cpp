#include "Engine.h"
#undef main

int main()
{
	Engine engine("YEET", 640, 360);

	engine.Update();

	return 0;
}