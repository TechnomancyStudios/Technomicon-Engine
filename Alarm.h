#pragma once
#include <SDL.h>

struct Alarm
{
	unsigned int timeTrigger = 0;
	unsigned int lastTime = 0;

	bool Trigger(int frames, void (*function)());
};