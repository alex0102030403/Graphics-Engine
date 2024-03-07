#include <gtc/matrix_transform.hpp>
#include "Input.h"
#include "Light.h"
#include "Shader.h"

Light::Light()
{
	m_ambient = glm::vec3(1.0f);
	m_diffuse = glm::vec3(1.0f);
	m_specular = glm::vec3(1.0f);
	m_transform.SetPosition(0.0f, 5.0f, 0.0f);

	GLfloat vertices[] = { 0.0f, 0.0f, 0.0f };
	GLfloat colors[] = { 1.0f, 1.0f, 1.0f };

	m_buffer.CreateBuffer(1);
	m_buffer.FillVBO(Buffer::VBOType::VertexBuffer, vertices, sizeof(vertices), Buffer::FillType::Once);
	m_buffer.FillVBO(Buffer::VBOType::ColorBuffer, colors, sizeof(colors), Buffer::FillType::Once);
}

Light::~Light()
{
	m_buffer.DestroyBuffer();
}

void Light::SetSpeed(GLfloat speed)
{
	m_speed = speed;
}

void Light::MoveUp()
{
	auto position = m_transform.GetPosition();
	position.y += m_speed;
	m_transform.SetPosition(position.x, position.y, position.z);
}

void Light::MoveDown()
{
	auto position = m_transform.GetPosition();
	position.y -= m_speed;
	m_transform.SetPosition(position.x, position.y, position.z);
}

void Light::MoveLeft()
{
	auto position = m_transform.GetPosition();
	position.x -= m_speed;
	m_transform.SetPosition(position.x, position.y, position.z);
}

void Light::MoveRight()
{
	auto position = m_transform.GetPosition();
	position.x += m_speed;
	m_transform.SetPosition(position.x, position.y, position.z);
}

void Light::MoveForward()
{
	auto position = m_transform.GetPosition();
	position.z -= m_speed;
	m_transform.SetPosition(position.x, position.y, position.z);
}

void Light::MoveBackward()
{
	auto position = m_transform.GetPosition();
	position.z += m_speed;
	m_transform.SetPosition(position.x, position.y, position.z);
}

void Light::Render(const Shader& shader)
{
	m_model = glm::mat4(1.0f);
	m_model = glm::translate(m_model, m_transform.GetPosition());

	shader.SendData("model", m_model);
	shader.SendData("isLit", false);
	shader.SendData("isTextured", false);
	
	m_buffer.LinkVBO(shader, "vertexIn", Buffer::VBOType::VertexBuffer, Buffer::ComponentType::XYZ, Buffer::DataType::FloatData);
	m_buffer.LinkVBO(shader, "colorIn", Buffer::VBOType::ColorBuffer, Buffer::ComponentType::RGB, Buffer::DataType::FloatData);

	glPointSize(20.0f);
	m_buffer.Render(Buffer::DrawType::Points);
}

void Light::SendToShader(const Shader& shader)
{
	auto position = m_transform.GetPosition();
	shader.SendData("light.position", position.x, position.y, position.z);
	shader.SendData("light.ambient", m_ambient.r, m_ambient.g, m_ambient.b);
	shader.SendData("light.diffuse", m_diffuse.r, m_diffuse.g, m_diffuse.b);
	shader.SendData("light.specular", m_specular.r, m_specular.g, m_specular.b);
}