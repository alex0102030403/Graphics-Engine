#pragma once

#include "gl.h"
#include <glm.hpp>
#include "Shader.h"
#include "Transform.h"

class Camera
{

public:

	Camera();

	void Set3DView();
	void SetSpeed(GLfloat speed);
	void SetViewport(GLint x, GLint y, GLsizei width, GLsizei height);

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void MoveForward();
	void MoveBackward();
	
	void Update() {}
	void SendToShader(const Shader& shader);

protected:

	GLfloat m_speed;
	Transform m_transform;

	glm::mat4 m_view;
	glm::mat4 m_proj;

	glm::vec3 m_up;
	glm::vec3 m_direction;

};