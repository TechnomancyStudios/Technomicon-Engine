#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Sprite.h"
#include "Audio.h"
#include "Tile.h"
#include "ECS.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include "GameObject.h"
#include "Player.h"
#include "Scene.h"
#include <string>

namespace Engine
{
	extern SDL_Window* mainWindow;
	extern SDL_Renderer* mainRenderer;
	extern SDL_Event e;

	extern Scene* mainScene;

	extern int poll;
	extern bool isRunning;

	extern SDL_GLContext gl_context;

	int Init(const char* title, int windowWidth, int windowHeight);
	void LoadScene(Scene* scene);
	void Update();
	void Render();
	void Quit();
}

/*
struct Engine
{
	Engine(const char* title,int windowWidth, int windowHeight);
	~Engine();

	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	SDL_Event e;

	SDL_GLContext glContext;

	int poll = 0;
	bool isRunning = true;

	int Init();
	void Update();
	void Render();

};
*/
