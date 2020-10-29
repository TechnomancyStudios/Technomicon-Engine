#include "Alarm.h"

bool Alarm::Trigger(int frames, void (*function)())
{
	if (lastTime == 0)
	{
		lastTime = SDL_GetTicks();
	}

	if ( SDL_GetTicks() >= ( lastTime + (frames * 16.7) ) )
	{
		(*function)();
		lastTime = (int)SDL_GetTicks();
		return true;
	}
	else
	{
		return false;
	}
}