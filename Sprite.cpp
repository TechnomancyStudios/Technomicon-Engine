#include "Sprite.h"

Sprite::Sprite()
{
	sprite_w = 64;
	sprite_h = 64;
	image_xscale = 1.0;
	image_yscale = 1.0;
	image_angle = 0.0;
	sprite_speed = 0;
	origin_x = 0;
	origin_y = 0;
	Setup();
}

Sprite::Sprite(std::string tpath)
{
	sprite_w = 0;
	sprite_h = 0;
	image_xscale = 1.0;
	image_yscale = 1.0;
	image_angle = 0.0;
	sprite_speed = 0;
	origin_x = 0;
	origin_y = 0;
	LoadSprite(tpath);
	Setup();
}


Sprite::~Sprite()
{
	SDL_FreeSurface(spriteSurface);
}

void Sprite::Setup()
{
	float vertices[] = {
			-0.5f,-0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Vertex 1 (X, Y)
			 0.5f,-0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Vertex 2 (X, Y)
			 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  // Vertex 3 (X, Y)
			-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f
	};

	unsigned int indices[] = {
		0,1,2,
		2,3,0
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
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

bool Sprite::LoadSprite(std::string tpath)
{
	//Load Image into Surface
	spriteSurface = IMG_Load(tpath.c_str());
	if (spriteSurface == NULL)
	{
		printf("UNABLE TO LOAD IMAGE!\n");
		return false;
	}
	else
	{
		sprite_w = spriteSurface->w;
		sprite_h = spriteSurface->h;
		glGenTextures(1, &spriteTexture);
		glBindTexture(GL_TEXTURE_2D, spriteTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spriteSurface->w, spriteSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, spriteSurface->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	return true;
}

void Sprite::Render(Shader shader, glm::mat4 m_view, glm::mat4 m_projection)
{
	glm::mat4 final_trans = glm::mat4(1.0f);
	m_world = glm::mat4(1.0f);
	m_world = glm::translate(m_world, glm::vec3(-(position.x+origin_x), -(position.y+origin_y), 1.0f));
	m_world = glm::rotate(m_world, glm::radians(image_angle), glm::vec3(0.0f, 0.0f, 1.0f));
	m_world = glm::scale(m_world, glm::vec3(-sprite_w*image_xscale, sprite_h* image_yscale, 1.0f));

	final_trans = m_projection * m_view * m_world;

	glUseProgram(shader.shaderID);
	unsigned int transformLoc = glGetUniformLocation(shader.shaderID, "transform");
	unsigned int timeUniform = glGetUniformLocation(shader.shaderID, "time");
	glUniform1f(timeUniform, (float)SDL_GetTicks());
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(final_trans));
	glBindTexture(GL_TEXTURE_2D, spriteTexture);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

Background::Background()
{
	sprite = new Sprite();
}

Background::Background(std::string tpath)
{
	sprite = new Sprite();
	//LoadSprite(sprite);
}

void Background::Render(SDL_Renderer* render)
{
	
}

void LoadSprite(Sprite* sprite, std::string tpath)
{
	//Load Image into Surface
	sprite->spriteSurface = IMG_Load(tpath.c_str());
	if (sprite->spriteSurface == NULL)
	{
		printf("UNABLE TO LOAD IMAGE!\n");
	}
	else
	{
		//Set Image Width and Height
		sprite->image_w = sprite->spriteSurface->w;
		sprite->image_h = sprite->spriteSurface->h;
		//Generate_Max_Index();
	}
}