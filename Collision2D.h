#pragma once
#include <glm/glm.hpp>

enum Collision2DType
{
	RECT,
	CIRCLE,
	POINT
};

class Collision2D
{
public:
	glm::vec2 colXY1 = { 0.0f, 0.0f };
	glm::vec2 colXY2 = { 0.0f, 0.0f };
	glm::vec2 origin = { 0.0f ,0.0f };

	Collision2DType colType;

	int collisionID = 0;

	bool canCollide;
};