#include "Engine.h"
#undef main

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int lenght;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
		char* message = (char*)malloc(lenght * sizeof(char));
		glGetShaderInfoLog(id, lenght, &lenght, message);
		std::cout << "Failed to Compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " Shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


namespace Engine
{
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	SDL_Event e;
	SDL_GLContext gl_context;
	Scene* mainScene;

	int poll = 0;
	bool isRunning = true;

	

	int Init(const char* title, int windowWidth, int windowHeight)
	{
		int failed = 0;
		//Initialize SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			SDL_Log("FAILED TO INITIALIZE SDL: %s", SDL_GetError());
			failed = 1;
		}
		else
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
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

		if (!failed)
		{
			//Create the Main Window
			mainWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
			//Create Main Renderer
			gl_context = SDL_GL_CreateContext(mainWindow);

			//mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
			/* Loading Extensions */
			glewExperimental = GL_TRUE;

			if (GLEW_OK != glewInit())
			{
				printf("Failed to initialize GLEW!");
			}

			glViewport(0, 0, windowWidth, windowHeight);
			glEnable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		return failed;
	}

	void Update()
	{
		glm::vec4 vec(1.0f,0.0f,0.0f,1.0f);
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

		glm::mat4 m_world = glm::mat4(1.0f);
		glm::mat4 m_view = glm::mat4(1.0f);
		glm::mat4 m_projection = glm::mat4(1.0f);
		//m_projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, 0.0f, 1000.0f);
		//m_view = glm::translate(m_view, glm::vec3(0.0f, 0.0f, 0.0f));

		glm::mat4 final_trans = glm::mat4(1.0f);

		std::cout << vec.x << vec.y << vec.z << std::endl;

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

		SDL_Surface* loadedSurface = IMG_Load("Test/down_stand.png");
		//loadedSurface = SDL_ConvertSurface(loadedSurface, SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32), 0);

		GLuint textureMap, texture2;
		glGenTextures(1, &textureMap);
		glBindTexture(GL_TEXTURE_2D, textureMap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedSurface->w, loadedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, loadedSurface->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		loadedSurface = IMG_Load("Test/test_sprite.png");

		glGenTextures(1, &texture2);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedSurface->w, loadedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, loadedSurface->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		const char* vertexShaderSource = R"glsl(
			#version 330 core
			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec3 aColor;
			layout (location = 2) in vec2 aTexCoord;
			
			uniform mat4 transform;

			out vec3 ourColor;
			out vec2 TexCoord;

			void main()
			{
				gl_Position = transform * vec4(aPos, 1.0f);
				ourColor = aColor;
				TexCoord = aTexCoord;
			}
		)glsl";

		const char* fragShaderSource = R"glsl(
			#version 330 core
			out vec4 FragColor;
  
			in vec3 ourColor;
			in vec2 TexCoord;

			uniform sampler2D ourTexture;

			void main()
			{
				vec4 tex = texture(ourTexture, vec2(TexCoord.x,TexCoord.y));
				FragColor = tex;
			}
		)glsl";

		GLuint shader = CreateShader(vertexShaderSource, fragShaderSource);

		

		GLuint vbo, vao, ebo;
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glBindVertexArray(vao);

		glGenBuffers(1, &ebo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		
		float xx = 0.0f;
		bool flip = false;

		float x_axis = 0.0f;
		float y_axis = 0.0f;
		float rot = 0.0f;

		while (isRunning)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				float speed = 0.1f;
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
								y_axis -= speed;
							break;
							case SDLK_s:
								y_axis += speed;
							break;
							case SDLK_a:
								x_axis += speed;
							break;
							case SDLK_d:
								x_axis -= speed;
							break;
							case SDLK_q:
								rot += 0.1f;
							break;
							case SDLK_e:
								rot -= 0.1f;
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

			m_world = glm::mat4(1.0f);
			m_view = glm::mat4(1.0f);
			m_projection = glm::mat4(1.0f);

			m_world = glm::translate(m_world, glm::vec3(0.0f, 0.0f, 0.0f));
			m_world = glm::scale(m_world, glm::vec3(1.0f, 1.0f, 1.0f));
			
			//m_world = glm::rotate(m_world,(float)SDL_GetTicks()/500, glm::vec3(1.0f,1.0f,1.0f));

			m_view = glm::translate(m_view, glm::vec3(x_axis, y_axis, -4.0f));
			m_view = glm::rotate(m_view, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
			m_view = glm::scale(m_view, glm::vec3(6.0f));
			//m_projection = glm::perspective(glm::radians(60.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);
			m_projection = glm::ortho(0.0f, 32.0f, 0.0f, 18.0f,0.1f,1000.0f);

			final_trans = m_projection * m_view * m_world;

			glClearColor(0.5f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glUseProgram(shader);
			unsigned int transformLoc = glGetUniformLocation(shader, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(final_trans));
			glBindTexture(GL_TEXTURE_2D, textureMap);
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);
			
			m_world = glm::mat4(1.0f);
			m_world = glm::translate(m_world, glm::vec3(1.0f, 1.0f, 0.0f));
			m_world = glm::scale(m_world, glm::vec3(1.0f, 1.0f, 1.0f));

			final_trans = m_projection * m_view * m_world;

			glUseProgram(shader);
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(final_trans));
			glBindTexture(GL_TEXTURE_2D, texture2);
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);
			
			SDL_GL_SwapWindow(mainWindow);
			
		}

		Quit();
	}


	void Render()
	{
		
	}

	void Quit()
	{
		//Destroy Window
		SDL_DestroyWindow(mainWindow);
		//Destroy Renderer
		SDL_DestroyRenderer(mainRenderer);
		//Clean up and Close Program
		
		//SDL_GL_DeleteContext(gl_context);
		SDL_GL_DeleteContext(gl_context);
		IMG_Quit();
		Mix_Quit();
		SDL_Quit();
	}

	void LoadScene(Scene* scene)
	{
		mainScene = scene;
	}
}