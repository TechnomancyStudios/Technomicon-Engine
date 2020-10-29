#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include "Shader.h"
#include <SDL.h>

struct Line
{
	glm::vec2 xy1 = {0.0f, 0.0f};
	glm::vec2 xy2 = { 0.0f, 0.0f };
	glm::vec3 color = { 0.0f, 1.0f, 0.0f };
	float lineThiccness = 1.0f;
	GLuint vbo, vao, ebo;
	glm::mat4 m_world = glm::mat4(1.0f);
	Line(glm::vec2 xy1, glm::vec2 xy2);
	void Draw(Shader shader, glm::mat4 m_view, glm::mat4 m_projection);
};