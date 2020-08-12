#pragma once
#include "Sprite.h"

struct Tile : public Sprite
{
	Tile();
	Tile(int t_x, int t_y, int t_w, int t_h, Sprite* t_spr, int x_in, int y_in);

	const int max_x_index = 7;
	const int max_y_index = 2;

	Sprite* tile_sprite;
	int x_index, y_index;


	void Render(SDL_Renderer* render);

};

class Tileset
{
public:
	Tileset(Sprite* t_sprite, int t_w, int t_h);

	enum TileState
	{
		TILE_SOLO = 0,
		TILE_BOTTOM_SOLO = 1,
		TILE_LEFT_SOLO = 2,
		TILE_TOP_SOLO = 3,
		TILE_RIGHT_SOLO = 4,
		TILE_BOTTOM_LEFT = 5,
		TILE_TOP_LEFT = 6,
		TILE_TOP_RIGHT = 7,
		TILE_BOTTOM_RIGHT = 8,
		TILE_LEFT = 9,
		TILE_TOP = 10,
		TILE_RIGHT = 11,
		TILE_BOTTOM = 12,
		TILE_SURROUND = 13
	};

	Sprite* tile_sprite;
	Tile* tile_grid[10][10];

	int tile_w, tile_h;
	
	void AddToGrid(int g_x, int g_y, int x_in, int y_in);
	void AddFromGrid(int grid[10][10]);
	void UpdateTiles();
	void RenderTiles(SDL_Renderer* render);

};