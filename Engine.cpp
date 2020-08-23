#include "Engine.h"
#undef main


Engine::Engine(const char* title, int windowWidth, int windowHeight)
{
	if (!Init())
	{
		//Create the Main Window
		mainWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
		//Create Main Renderer
		mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
	}

}

int Engine::Init()
{
	int failed = 0;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("FAILED TO INITIALIZE SDL: %s", SDL_GetError());
		failed = 1;
	}

	//Initialize SDL Image
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		SDL_Log("FAILED TO INITIALIZE SDL Image: %s", IMG_GetError());
		failed = 1;
	}

	//Initialize SDL Mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		failed = 1;
	}
	return failed;
}

void Engine::Update()
{
	while (isRunning)
	{
	
	}

	delete this;
}

void Engine::Render()
{
	SDL_RenderClear(mainRenderer);
	SDL_RenderPresent(mainRenderer);
}

Engine::~Engine()
{
	//Destroy Window
	SDL_DestroyWindow(mainWindow);
	//Destroy Renderer
	SDL_DestroyRenderer(mainRenderer);
	//Clean up and Close Program
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}