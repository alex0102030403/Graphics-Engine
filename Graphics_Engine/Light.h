#pragma once

#include "gl.h"
#include <glm.hpp>
#include "Buffer.h"
#include "Shader.h"
#include "Transform.h"

class Light
{

public:

	Light();
	~Light();

	void SetSpeed(GLfloat speed);

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void MoveForward();
	void MoveBackward();

	void Update() {}
	void Render(const Shader& shader);
	void SendToShader(const Shader& shader);
	
private:

	Buffer m_buffer;
	Transform m_transform;

	GLfloat m_speed;
	glm::mat4 m_model;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

};