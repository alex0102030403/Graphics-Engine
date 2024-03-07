#pragma once

#include "gl.h"
#include <glm.hpp>
#include "Buffer.h"
#include "Shader.h"
#include "Transform.h"

class Grid
{

public:

	Grid();
	
	Transform& GetTransform();

	void Update() {}
	void Render(const Shader& shader);

private:

	Buffer m_buffer;
	Transform m_transform;

	glm::mat4 m_model;
	glm::vec3 m_position;
	glm::vec3 m_rotation;

};