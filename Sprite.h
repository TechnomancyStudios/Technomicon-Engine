#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <string>
#include <SDL_image.h>
#include "Shader.h"

class Sprite
{
public:
	Sprite();
	Sprite(std::string tpath);
	~Sprite();
	//Setup vertex data
	void Setup();
	//Loads texture
	bool LoadSprite(std::string tpath);
	//Frees texture
	void Free();
	//Renders Sprite
	virtual void Render(Shader shader, glm::mat4 m_view, glm::mat4 m_projection);
	//Generate Sprite Max Index
	void Generate_Max_Index();

	int image_index = 0;
	float image_angle = 0.0f;
	int image_max_index = -1;
	int image_w = 0, image_h = 0;
	float image_xscale = 1.0f, image_yscale = 1.0f;
	float sprite_w = 0.0f, sprite_h = 0.0f;

	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 origin = glm::vec2(0.0f);

	int isAnimated = false;

	GLuint vbo, vao, ebo;
	glm::mat4 m_world = glm::mat4(1.0f);

	SDL_Surface* spriteSurface = NULL;
	GLuint spriteTexture;
private:
	SDL_RendererFlip flip = SDL_FLIP_NONE;
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
	Background(std::string tpath);

	void Render();
};

void LoadSprite(Sprite* sprite, std::string tpath);