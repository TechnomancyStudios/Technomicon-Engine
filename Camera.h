#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Camera
{
	float x, y;
	float rot;
	float zoom;
	float view_w;
	float view_h;

	glm::vec2 position;
	glm::vec2 followPosition = {0.0f,0.0f};
	glm::mat4 m_view = glm::mat4(1.0f);
	glm::mat4 m_projection = glm::mat4(1.0f);

	Camera(float x, float y, float rot, float zoom, float view_w, float view_h);

	void SetZoom(float zoom);
	void SetPosition(float x, float y);

	void Update();
	
};