#pragma once
#include <SDL.h>
#include <glm/glm.hpp>

enum MouseButton
{
	LEFTMOUSEBUTTON = 1,
	MIDDLEMOUSEBUTTON = 2,
	RIGHTMOUSEBUTTON = 3
};

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
	glm::vec4 worldPosition;
	glm::vec2 screenPosition;
	Uint32 oldState = SDL_GetMouseState(NULL, NULL);
	bool isMouseButtonPressed(MouseButton button);
};