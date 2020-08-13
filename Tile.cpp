#include "Tile.h"

Tile::Tile()
{

}

Tile::Tile(int t_x, int t_y, int t_w, int t_h, Sprite* t_spr, int x_in, int y_in)
{
	sprite_x = t_x;
	sprite_y = t_y;
	sprite_w = t_w;
	sprite_h = t_h;
	tile_sprite = t_spr;
	x_index = x_in;
	y_index = y_in;
}

void Tile::Render(SDL_Renderer* render)
{
	if (tile_sprite != NULL)
	{
		SDL_Rect spriteRect = { sprite_x, sprite_y, sprite_w, sprite_h };
		SDL_Rect clipRect = { sprite_w * x_index, sprite_h * y_index, sprite_w, sprite_h };

		SDL_RenderSetScale(render,1.0f,1.0f);
		SDL_RenderCopyEx(render, tile_sprite->spriteTexture, &clipRect, &spriteRect, image_angle, { 0 }, SDL_FLIP_NONE);
	}
}

Tileset::Tileset(Sprite* t_sprite, int t_w, int t_h)
{
	tile_sprite = t_sprite;
	tile_w = t_w;
	tile_h = t_h;
	tile_grid[10][10] = NULL;
}

void Tileset::AddToGrid(int g_x, int g_y, int x_in, int y_in)
{
	tile_grid[g_y][g_x] = new Tile(tile_w*g_x,tile_h*g_y,tile_w,tile_h,tile_sprite,x_in,y_in);
}

void Tileset::AddFromGrid(int grid[10][10])
{
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			if (grid[y][x] == 0)
			{
				tile_grid[y][x] = NULL;
			}
		}
	}
}

void Tileset::UpdateTiles()
{
	for (int y = 0; y <= 9; y++)
	{
		for (int x = 0; x <= 9; x++)
		{
			bool t_top = false;
			bool t_bottom = false;
			bool t_left = false;
			bool t_right = false;

			if (x - 1 >= 0)
			{
				if (tile_grid[y][x - 1] != NULL)
					t_left = true;
			}
			if (x + 1 <= 9)
			{
				if (tile_grid[y][x + 1] != NULL)
					t_right = true;
			}
			if (y - 1 >= 0)
			{
				if (tile_grid[y - 1][x] != NULL)
					t_top = true;
			}
			if (y + 1 <= 9)
			{
				if (tile_grid[y + 1][x] != NULL)
					t_bottom = true;
			}
			
			if (tile_grid[y][x] != NULL)
			{
				if (!t_top && !t_bottom && !t_left && !t_right)
					tile_grid[y][x]->x_index = TILE_SOLO;
				else if (t_top && !t_bottom && !t_left && !t_right)
					tile_grid[y][x]->x_index = TILE_BOTTOM_SOLO;
				else if (!t_top && !t_bottom && !t_left && t_right)
					tile_grid[y][x]->x_index = TILE_LEFT_SOLO;
				else if (!t_top && t_bottom && !t_left && !t_right)
					tile_grid[y][x]->x_index = TILE_TOP_SOLO;
				else if (!t_top && !t_bottom && t_left && !t_right)
					tile_grid[y][x]->x_index = TILE_RIGHT_SOLO;
				else if (t_top && !t_bottom && !t_left && t_right)
					tile_grid[y][x]->x_index = TILE_BOTTOM_LEFT;
				else if (!t_top && t_bottom && !t_left && t_right)
					tile_grid[y][x]->x_index = TILE_TOP_LEFT;
				else if (!t_top && t_bottom && t_left && !t_right)
					tile_grid[y][x]->x_index = TILE_TOP_RIGHT;
				else if (t_top && !t_bottom && t_left && !t_right)
				{
					tile_grid[y][x]->x_index = TILE_BOTTOM_RIGHT - 8;
					tile_grid[y][x]->y_index = 1;
				}
				else if (t_top && t_bottom && !t_left && t_right)
				{
					tile_grid[y][x]->x_index = TILE_LEFT - 8;
					tile_grid[y][x]->y_index = 1;
				}
				else if (t_top && t_bottom && t_left && !t_right)
				{
					tile_grid[y][x]->x_index = TILE_RIGHT - 8;
					tile_grid[y][x]->y_index = 1;
				}
				else if (!t_top && t_bottom && t_left && t_right)
				{
					tile_grid[y][x]->x_index = TILE_TOP - 8;
					tile_grid[y][x]->y_index = 1;
				}
				else if (t_top && !t_bottom && t_left && t_right)
				{
					tile_grid[y][x]->x_index = TILE_BOTTOM - 8;
					tile_grid[y][x]->y_index = 1;
				}
				else if (t_top && t_bottom && t_left && t_right)
				{
					tile_grid[y][x]->x_index = TILE_SURROUND - 8;
					tile_grid[y][x]->y_index = 1;
				}
				else if (!t_top && !t_bottom && t_left && t_right)
				{
					tile_grid[y][x]->x_index = TILE_TOP_BOTTOM - 8;
					tile_grid[y][x]->y_index = 1;
				}
				else if (t_top && t_bottom && !t_left && !t_right)
				{
					tile_grid[y][x]->x_index = TILE_LEFT_RIGHT - 8;
					tile_grid[y][x]->y_index = 1;
				}
			}
		}
	}
}

void Tileset::RenderTiles(SDL_Renderer* render)
{
	for (int y = 0; y <= 9; y++)
	{
		for (int x = 0; x <= 9; x++)
		{
			if(tile_grid[y][x] != NULL)
				tile_grid[y][x]->Render(render);
		}
	}
	
}