#include <SDL.h>
#include "Core/Sprite.h"
#include "Core/Audio.h"
#include "Core/Tile.h"
#undef main

int main()
{
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	SDL_Event e;
	int poll = 0;
	bool isRunning = true;

	Sprite* testSprite = new Sprite(64,64,215,265,(215/2),(265/2),1);
	Sprite* tileSprite = new Sprite(0, 0, 224, 64, 0, 0, 1);
	Tileset* tset = new Tileset(tileSprite, 32, 32);

	MusicPlayer* musicPlayer = new MusicPlayer();
	

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("FAILED TO INITIALIZE SDL: %s", SDL_GetError());
		return 1;
	}
	//Initialize SDL Image
	if (!(IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG))
	{
		SDL_Log("FAILED TO INITIALIZE SDL Image: %s", IMG_GetError());
		return 1;
	}
	//Initialize SDL Mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return 1;
	}

	//Create the Main Window
	mainWindow = SDL_CreateWindow("YEET", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 360, SDL_WINDOW_OPENGL);
	//Create Main Renderer
	mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

	testSprite->LoadSprite("Test/test_sprite.png", mainRenderer);
	tileSprite->LoadSprite("Test/test_tile.png", mainRenderer);

	musicPlayer->AddTrackToMap("Test/Mesospheratical.wav","meso");
	musicPlayer->AddTrackToMap("Test/j a z z y.wav", "jazz");
	//musicPlayer->AddTrackToMap("Test/GrowingPanes.mp3", "gp");

	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			tset->AddToGrid(x, y, 0, 0);
		}
	}
	
	int grid[10][10] = {
		1,1,1,1,0,0,0,0,0,0,
		1,1,1,1,0,0,0,0,0,0,
		0,0,0,0,0,0,1,1,1,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,1,0,0,0,0,0,
		0,0,0,1,1,1,0,0,0,0,
		0,0,0,0,1,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		1,1,0,0,1,1,1,1,0,0,
		0,0,0,0,0,0,0,0,0,0
	};

	tset->AddFromGrid(grid);
	tset->UpdateTiles();

	musicPlayer->PlayTrack("jazz", -1);

	//Game Loop
	while (isRunning)
	{
		poll = SDL_PollEvent(&e);

		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				isRunning = false;
			}
		}
		testSprite->image_angle+=0.01;
		SDL_RenderClear(mainRenderer);
		SDL_SetRenderDrawColor(mainRenderer, 255, 0, 0, 1);
		testSprite->Render(mainRenderer);
		tset->RenderTiles(mainRenderer);
		SDL_RenderPresent(mainRenderer);
	}

	//Destroy Window
	SDL_DestroyWindow(mainWindow);
	//Clean up and Close Program
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();

	return 0;
}