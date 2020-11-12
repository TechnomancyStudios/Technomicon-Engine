#include "Input.h"

bool Mouse::isMouseButtonPressed(MouseButton button)
{
	Uint32 state = SDL_GetMouseState(NULL, NULL);

	if (state == button)
	{
		if (button == oldState)
		{
			return 0;
		}
		else
		{
			oldState = state;
			return 1;
		}
	}
	else
	{
		oldState = state;
		return 0;
	}
}