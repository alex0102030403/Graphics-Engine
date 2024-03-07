#include <gtc\matrix_transform.hpp>
#include "Camera.h"
#include "Input.h"
#include "Shader.h"

Camera::Camera()
{
	m_view = glm::mat4(1.0f);
	m_proj = glm::mat4(1.0f);
	m_direction = glm::vec3(0.0f, 0.0f, -1.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_transform.SetPosition(0.0f, 3.0f, 20.0f);
}

void Camera::Set3DView()
{
	auto FOV = 45.0f;
	auto aspectRatio = 1280.0f / 720.0f;
	m_proj = glm::perspective(FOV, aspectRatio, 0.001f, 1000.0f);
}

void Camera::SetSpeed(GLfloat speed)
{
	m_speed = speed;
}

void Camera::SetViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glViewport(x, y, width, height);
}

void Camera::MoveUp()
{
	auto position = m_transform.GetPosition();
	position.y += m_speed;
	m_transform.SetPosition(position.x, position.y, position.z);
}

void Camera::MoveDown()
{
	auto position = m_transform.GetPosition();
	position.y -= m_speed;
	m_transform.SetPosition(position.x, position.y, position.z);
}

void Camera::MoveLeft()
{
	auto position = m_transform.GetPosition();
	position.x -= m_speed;
	m_transform.SetPosition(position.x, position.y, position.z);
}

void Camera::MoveRight()
{
	auto position = m_transform.GetPosition();
	position.x += m_speed;
	m_transform.SetPosition(position.x, position.y, position.z);
}

void Camera::MoveForward()
{
	auto position = m_transform.GetPosition();
	position.z -= m_speed;
	m_transform.SetPosition(position.x, position.y, position.z);
}

void Camera::MoveBackward()
{
	auto position = m_transform.GetPosition();
	position.z += m_speed;
	m_transform.SetPosition(position.x, position.y, position.z);
}

void Camera::SendToShader(const Shader& shader)
{
	auto position = m_transform.GetPosition();
	m_view = glm::lookAt(position, position + m_direction, m_up);
	shader.SendData("proj", m_proj);
	shader.SendData("view", m_view);
	shader.SendData("cameraPosition", position.x, position.y, position.z);
}