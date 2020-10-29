/*
#include "Engine.h"
#undef main

int main()
{
	Engine app;
	app.Init("Suits: Absolute Power", 1280, 720);

	app.Update();

	return 0;
}


void Engine::Update()
{
	Shader shader = { CreateShader("Shaders/default.vs", "Shaders/default.fs"), "Default" };
	Shader rainbowShader = { CreateShader("Shaders/default.vs", "Shaders/rainbow.fs"), "Rainbow" };
	Shader blurShader = { CreateShader("Shaders/default_pp.vs", "Shaders/blur.fs"), "DefaultPP" };
	Shader screenShader = { CreateShader("Shaders/default_pp.vs", "Shaders/bloom.fs"), "DefaultPP" };

	Sprite sprite("Test/bg_1.png");
	Sprite sprite2("Test/jeb.png");
	Sprite sprite3("Test/jeb.png");

	mainScene = nullptr;

	glm::mat4 m_view = glm::mat4(1.0f);
	glm::mat4 m_projection = glm::mat4(1.0f);

	//Create Framebuffer
	Framebuffer framebuffer, bloombuffer;


	float xx = 0.0f;
	bool flip = false;

	float x_axis = 0.0f;
	float y_axis = 0.0f;
	float rot = 0.0f;
	float zoom = 1.0f;

	while (isRunning)
	{
		while(SDL_PollEvent(&e) != 0 && SDL_WaitEvent(&e))
		{
			//User requests quit
			float speed = 1.0f;
			
			switch (e.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_w:
					y_axis += speed;
					break;
				case SDLK_s:
					y_axis -= speed;
					break;
				case SDLK_a:
					x_axis -= speed;
					break;
				case SDLK_d:
					x_axis += speed;
					break;
				case SDLK_q:
					zoom += 0.1f;
					break;
				case SDLK_e:
					zoom -= 0.1f;
					break;
				}
			}
			break;
			
			}

		}

		if (mainScene != nullptr)
			mainScene->Update();

		if (!flip)
		{
			if (xx < 1)
				xx += 0.01f;
			else
				flip = true;
		}
		else
		{
			if (xx > 0)
				xx -= 0.01f;
			else
				flip = false;
		}

		if (e.type == SDL_MOUSEBUTTONDOWN)
			sprite2.image_angle += 2.0f;


		int x, y;
		SDL_GetMouseState(&x, &y);

		glm::vec4 mouseVec = glm::vec4((float)x / zoom, (float)y / zoom, 1.0f, 1.0f);
		sprite.position = glm::vec2(1280.0f / 2.0f, 720.0f / 2.0f);

		m_view = glm::mat4(1.0f);
		m_projection = glm::mat4(1.0f);

		//m_view = glm::translate(m_view, glm::vec3(x_axis, y_axis, -4.0f));
		m_view = glm::rotate(m_view, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
		m_view = glm::scale(m_view, glm::vec3(zoom));
		m_view = glm::translate(m_view, glm::vec3(x_axis + (1280.0f - (1280.0f / zoom)) / 2.0f, y_axis + (720.0f - (720.0f / zoom)) / 2.0f, -4.0f));
		//m_projection = glm::perspective(glm::radians(60.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);
		m_projection = glm::ortho(0.0f, -1280.0f, -720.0f, 0.0f, 0.1f, 1000.0f);

		mouseVec = m_view * mouseVec;
		mouseVec = glm::vec4((mouseVec.x / zoom), mouseVec.y / zoom, 1.0f, 1.0f);
		//std::cout << mouseVec.x << " " << mouseVec.y << std::endl;

		sprite2.position = glm::vec2(1280.0f/2.0f, 720.0f / 2.0f);
		sprite3.position = mouseVec;



		// DRAW TO SCREEN
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.frameBuffer);

		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glEnable(GL_DEPTH_TEST);

		sprite.Render(shader, m_view, m_projection);
		sprite2.Render(rainbowShader, m_view, m_projection);
		sprite3.Render(shader, m_view, m_projection);
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		glBindFramebuffer(GL_FRAMEBUFFER, bloombuffer.frameBuffer);

		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		blurShader.Use();
		glBindTexture(GL_TEXTURE_2D, framebuffer.frameTexture[1]);
		bloombuffer.Render();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClearColor(2.0f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, bloombuffer.frameTexture[1]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, framebuffer.frameTexture[0]);

		screenShader.Use();

		screenShader.SetUniform1i("fragTex", 0);
		screenShader.SetUniform1i("brightTex", 1);

		framebuffer.Render();

		glBindTexture(GL_TEXTURE_2D, 0);

		SDL_GL_SwapWindow(mainWindow);

	}

	Quit();
}
*/