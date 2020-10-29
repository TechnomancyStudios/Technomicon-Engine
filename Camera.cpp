#include "Camera.h"

Camera::Camera(float x, float y, float rot, float zoom, float view_w, float view_h)
{
	position = { x, y };
	this->rot = rot;
	this->zoom = zoom;
	this->view_w = view_w;
	this->view_h = view_h;
}

void Camera::SetPosition(float x, float y)
{
	position = { x, y };
}

void Camera::SetZoom(float zoom)
{
	this->zoom = zoom;
}

void Camera::Update()
{
	m_view = glm::mat4(1.0f);
	m_projection = glm::mat4(1.0f);

	//position = (position - followPosition) * 0.01f;

	m_view = glm::rotate(m_view, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
	m_view = glm::scale(m_view, glm::vec3(zoom));
	m_view = glm::translate(m_view, glm::vec3(position.x + (view_w - (view_w / zoom)) / 2.0f, position.y + (view_h - (view_h / zoom)) / 2.0f, -4.0f));
	
	m_projection = glm::ortho(0.0f, -view_w, -view_h, 0.0f, 0.1f, 1000.0f);
}