#include "Shapes.h"

Line::Line(glm::vec2 xy1, glm::vec2 xy2)
{
	this->xy1 = xy1;
	this->xy2 = xy2;

	float vertices[] = {
		0.0f, 0.0f,
		1.0f, 0.0f
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
	glBindVertexArray(0);
}

void Line::Draw(Shader shader, glm::mat4 m_view, glm::mat4 m_projection)
{
	float yeet = (xy2.y - xy1.y) / (xy2.x - xy1.x);
	float angle = glm::atan(yeet);
	glm::mat4 final_trans = glm::mat4(1.0f);
	m_world = glm::mat4(1.0f);
	m_world = glm::translate(m_world, glm::vec3( (xy1.x), (xy1.y), 1.0f));
	float sum = xy2.x + glm::abs(xy2.y);
	m_world = glm::rotate(m_world, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	m_world = glm::scale(m_world, glm::vec3( -glm::cos(angle)*(xy2.x - xy1.x)-glm::sin(angle) * (xy2.y - xy1.y), 1.0f, 1.0f));
	
	
	final_trans = m_projection * m_view * m_world;

	glUseProgram(shader.shaderID);
	unsigned int transformLoc = glGetUniformLocation(shader.shaderID, "transform");
	unsigned int timeUniform = glGetUniformLocation(shader.shaderID, "time");
	unsigned int colorUniform = glGetUniformLocation(shader.shaderID, "color");
	glUniform1f(timeUniform, (float)SDL_GetTicks());
	glUniform3f(colorUniform, color.x, color.y, color.z);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(final_trans));
	glBindVertexArray(vao);
	
	glLineWidth(lineThiccness);
	glDrawArrays(GL_LINES, 0, 2);
	glLineWidth(1.0f);
	glBindVertexArray(0);
}