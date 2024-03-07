#include "Object.h"

Object::Object(Grid* parentGrid)
{
	m_isTextured = false;
	m_parentGrid = parentGrid;
	m_color = glm::vec4(1.0f);
	m_normal = glm::mat3(1.0f);
}

void Object::IsTextured(bool isTextured)
{
	m_isTextured = isTextured;
}

bool Object::IsTextured() const
{
	return m_isTextured;
}

Transform& Object::GetTransform()
{
	return m_transform;
}

const glm::vec4& Object::GetColor() const
{
	return m_color;
}

void Object::Render(const Shader& shader)
{
	m_normal = glm::inverse(glm::mat3(m_transform.GetMatrix()));
	
	if (m_parentGrid)
	{
		shader.SendData("model", m_parentGrid->GetTransform().GetMatrix() * m_transform.GetMatrix());
	}
	
	else
	{
		shader.SendData("model", m_transform.GetMatrix());
	}

	shader.SendData("normal", m_normal);
}