#pragma once
#include <SDL.h>
#include <glm/glm.hpp>

struct KeyboardHandler
{
	const Uint8* oldState = SDL_GetKeyboardState(NULL);
	
	bool isKeyDown(SDL_Keycode key)
	{
		const Uint8* state = SDL_GetKeyboardState(NULL);

		return (state[key]);
	}

	bool isKeyPressed(SDL_Keycode key)
	{
		const Uint8* state = SDL_GetKeyboardState(NULL);

		if (oldState[key] == state[key])
		{
			return 0;
		}
		else
		{
			oldState = SDL_GetKeyboardState(NULL);
			return (state[key]);
		}
	}

};

struct Mouse
{
	int x, y;
	bool isMouseButtonPressed();
	void Update();
};