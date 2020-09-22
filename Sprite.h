#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>


class Sprite
{
public:
	Sprite();
	Sprite(std::string tpath, int w, int h);
	Sprite(int s_x, int s_y, int s_w, int s_h, int o_x, int o_y, int speed);
	~Sprite();
	//Loads texture
	bool LoadSprite(std::string tpath, SDL_Renderer* render);
	//Frees texture
	void Free();
	//Renders Sprite
	virtual void Render(SDL_Renderer* render);
	void RenderRect(SDL_Renderer* render);
	//Generate Sprite Max Index
	void Generate_Max_Index();
	//Set Sprite Flip State
	void Flip_Sprite(SDL_RendererFlip sflip);
	//Set Origin of Sprite
	void Set_Origin(int x, int y);

	int image_index = 0;
	double image_angle = 0.0;
	int image_max_index = -1;
	int image_w = 0, image_h = 0;
	int origin_x = 0, origin_y = 0;
	float image_xscale = 1, image_yscale = 1;
	int sprite_x = 0, sprite_y = 0, sprite_w = 0, sprite_h = 0;
	int isAnimated = false;

	SDL_Texture* spriteTexture = NULL;
private:
	SDL_Point origin;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_Rect* rect;
	int sprite_speed;
};

struct Background
{
	Sprite* sprite;

	int x_offset = 0;
	int y_offset = 0;
	int x_speed = 0;
	int y_speed = 0;

	Background();
	Background(std::string tpath, SDL_Renderer* renderer);

	void Render(SDL_Renderer* render);
};

void LoadSprite(Sprite* sprite, std::string tpath, SDL_Renderer* render);