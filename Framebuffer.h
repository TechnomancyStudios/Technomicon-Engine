#pragma once
#include <GL/glew.h>
#include <iostream>
#include "Shader.h"

struct Framebuffer
{
	GLuint frameBuffer, frameTexture[2], rbo, vao, vbo, ebo;
	Framebuffer();
	void Render();
};

