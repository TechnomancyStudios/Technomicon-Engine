#pragma once
#include <SDL.h>
#include "Sprite.h"
#include "Audio.h"
#include "Tile.h"
#include "ECS.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

struct Engine
{
	Engine(const char* title,int windowWidth, int windowHeight);
	~Engine();

	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	SDL_Event e;

	int poll = 0;
	bool isRunning = true;

	int Init();
	void Update();
	void Render();

};

