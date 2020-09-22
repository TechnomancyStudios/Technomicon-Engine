#include "Sprite.h"

Sprite::Sprite()
{
	sprite_x = 0;
	sprite_y = 0;
	sprite_w = 64;
	sprite_h = 64;
	image_xscale = 1.0;
	image_yscale = 1.0;
	image_angle = 0.0;
	sprite_speed = 0;
	origin_x = 0;
	origin_y = 0;
	origin = { origin_x,origin_y };
	rect = new SDL_Rect({ 0,0,64,64 });
}

Sprite::Sprite(std::string tpath, int w, int h)
{
	sprite_x = 0;
	sprite_y = 0;
	sprite_w = w;
	sprite_h = h;
	image_xscale = 1.0;
	image_yscale = 1.0;
	image_angle = 0.0;
	sprite_speed = 0;
	origin_x = 0;
	origin_y = 0;
	origin = { origin_x,origin_y };
	rect = new SDL_Rect({ 0,0,w,h });

	LoadSprite(tpath,nullptr);
}

Sprite::Sprite(int s_x, int s_y, int s_w, int s_h, int o_x, int o_y, int speed)
{
	sprite_x = s_x;
	sprite_y = s_y;
	sprite_w = s_w;
	sprite_h = s_h;
	image_xscale = 1.0;
	image_yscale = 1.0;
	image_angle = 0.0;
	sprite_speed = speed;
	origin_x = o_x;
	origin_y = o_y;
	origin = { origin_x,origin_y };
	rect = new SDL_Rect({ s_x,s_y,s_w,s_h });
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(spriteTexture);
}

void Sprite::Generate_Max_Index()
{
	//Determines the number of frames in an image based on the sprite width and height
	int x_index = image_w / sprite_w;
	int y_index = image_h / sprite_h;

	for (int i = 0; i < y_index; i++)
	{
		for (int j = 0; j < x_index; j++)
		{
			image_max_index++;
		}
	}
}

bool Sprite::LoadSprite(std::string tpath, SDL_Renderer* render)
{
	//Load Image into Surface
	SDL_Surface* loadedSurface = IMG_Load(tpath.c_str());
	if (loadedSurface == NULL)
	{
		printf("UNABLE TO LOAD IMAGE!\n");
		return false;
	}
	else
	{
		//Create Texture from Surface
		spriteTexture = SDL_CreateTextureFromSurface(render, loadedSurface);
		if (spriteTexture == NULL)
		{
			printf("THIS TEXTURE COULDN'T BE CREATED YO!\n");
		}
		//Set Image Width and Height
		image_w = loadedSurface->w;
		image_h = loadedSurface->h;
		Generate_Max_Index();
		//Gets rid of loadedSurface to save memory
		SDL_FreeSurface(loadedSurface);
	}
	return true;
}

void Sprite::Flip_Sprite(SDL_RendererFlip sflip)
{
	flip = sflip;
}

void Sprite::Set_Origin(int x, int y)
{
	origin.x = x;
	origin.y = y;
}

void Sprite::Render(SDL_Renderer* render)
{
	SDL_Rect spriteRect;
	SDL_Rect clipRect;

	if (sprite_speed > 0)
	{
		spriteRect = { sprite_x,sprite_y,(int)(sprite_w * image_xscale),(int)(sprite_h * image_yscale) };
		clipRect = { sprite_w * (image_index++ / sprite_speed),0,sprite_w,sprite_h };

		if ((image_index / sprite_speed > image_max_index))
		{
			image_index = 0;
		}
		Set_Origin(origin_x * image_xscale, origin_y * image_yscale);
		SDL_RenderCopyEx(render, spriteTexture, &clipRect, &spriteRect, image_angle, &origin, flip);
	}
	else
	{
		spriteRect = { sprite_x,sprite_y,(int)(sprite_w * image_xscale),(int)(sprite_h * image_yscale) };
		clipRect = { sprite_w, 0, sprite_w, sprite_h };

		Set_Origin(origin_x * image_xscale, origin_y * image_yscale);
		SDL_RenderCopyEx(render, spriteTexture, NULL, &spriteRect, image_angle, &origin, flip);
	}
}

void Sprite::RenderRect(SDL_Renderer* render)
{
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	SDL_RenderFillRect(render, rect);
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
}


Background::Background()
{
	sprite = new Sprite();
}

Background::Background(std::string tpath, SDL_Renderer* renderer)
{
	sprite = new Sprite();
	LoadSprite(sprite, tpath, renderer);
}

void Background::Render(SDL_Renderer* render)
{
	if (this->sprite != nullptr)
	{
		sprite->sprite_x = x_offset + x_speed;
		sprite->sprite_y = y_offset + y_speed;
		sprite->Render(render);
	}
}

void LoadSprite(Sprite* sprite, std::string tpath, SDL_Renderer* render)
{
	//Load Image into Surface
	SDL_Surface* loadedSurface = IMG_Load(tpath.c_str());
	if (loadedSurface == NULL)
	{
		printf("UNABLE TO LOAD IMAGE!\n");
	}
	else
	{
		//Create Texture from Surface
		sprite->spriteTexture = SDL_CreateTextureFromSurface(render, loadedSurface);
		if (sprite->spriteTexture == NULL)
		{
			printf("THIS TEXTURE COULDN'T BE CREATED YO!\n");
		}
		sprite->sprite_w = loadedSurface->w;
		sprite->sprite_h = loadedSurface->h;
		sprite->image_w = loadedSurface->w;
		sprite->image_h = loadedSurface->h;
		//Gets rid of loadedSurface to save memory
		SDL_FreeSurface(loadedSurface);
	}
}