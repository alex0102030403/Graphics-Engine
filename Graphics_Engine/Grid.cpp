#include <gtc/matrix_transform.hpp>
#include "Grid.h"
#include "Input.h"

Grid::Grid()
{
	const auto SIZE = 10;
	const auto QUADRANTS = 4;
	const auto VERTICES_PER_LINE = 2;

	const auto BYTES_PER_LINE_VERTEX =
		VERTICES_PER_LINE * static_cast<GLuint>(Buffer::ComponentType::XYZ) * sizeof(GLint);

	const auto BYTES_PER_LINE_COLOR =
		VERTICES_PER_LINE * static_cast<GLuint>(Buffer::ComponentType::RGBA) * sizeof(GLfloat);

	const auto BYTES_VERTEX_VBO = (SIZE + 1) * QUADRANTS * BYTES_PER_LINE_VERTEX;
	const auto BYTES_COLOR_VBO = (SIZE + 1) * QUADRANTS * BYTES_PER_LINE_COLOR;

	m_buffer.CreateBuffer((SIZE + 1) * QUADRANTS * VERTICES_PER_LINE, false);
	
	m_buffer.FillVBO(Buffer::VBOType::VertexBuffer,
		(GLint*)nullptr, BYTES_VERTEX_VBO, Buffer::FillType::Ongoing);
	
	m_buffer.FillVBO(Buffer::VBOType::ColorBuffer,
		(GLfloat*)nullptr, BYTES_COLOR_VBO, Buffer::FillType::Ongoing);

	auto offsetColor = 0U;
	auto offsetVertex = 0U;

	//==================================
	//Negative vertical lines
	//==================================

	for (int i = 0; i <= SIZE; i++) 
	{
		GLint vertices[] = { -SIZE + i, 0,  SIZE,      //first vertex
							 -SIZE + i, 0, -SIZE };    //second vertex

		GLfloat colors[] = { 0.5f, 0.5f, 0.5f, 1.0f,
							 0.5f, 0.5f, 0.5f, 1.0f };

		m_buffer.AppendVBO(Buffer::VBOType::VertexBuffer, vertices, sizeof(vertices), offsetVertex);
		m_buffer.AppendVBO(Buffer::VBOType::ColorBuffer, colors, sizeof(colors), offsetColor);

		offsetVertex += BYTES_PER_LINE_VERTEX;
		offsetColor += BYTES_PER_LINE_COLOR;
	}

	//==================================
	//Positive vertical lines
	//==================================

	for (int i = 1; i < SIZE + 1; i++) 
	{
		GLint vertices[] = { 0 + i, 0,  SIZE,      //first vertex
							 0 + i, 0, -SIZE };    //second vertex

		GLfloat colors[] = { 0.5f, 0.5f, 0.5f, 1.0f,
							 0.5f, 0.5f, 0.5f, 1.0f };

		m_buffer.AppendVBO(Buffer::VBOType::VertexBuffer, vertices, sizeof(vertices), offsetVertex);
		m_buffer.AppendVBO(Buffer::VBOType::ColorBuffer, colors, sizeof(colors), offsetColor);

		offsetVertex += BYTES_PER_LINE_VERTEX;
		offsetColor += BYTES_PER_LINE_COLOR;
	}

	//==================================
	//Negative horizontal lines
	//==================================

	for (int i = 0; i <= SIZE; i++)
	{
		GLint vertices[] = { -SIZE, 0, -SIZE + i,       //first vertex
							  SIZE, 0, -SIZE + i };     //second vertex

		GLfloat colors[] = { 0.5f, 0.5f, 0.5f, 1.0f,
							 0.5f, 0.5f, 0.5f, 1.0f };

		m_buffer.AppendVBO(Buffer::VBOType::VertexBuffer, vertices, sizeof(vertices), offsetVertex);
		m_buffer.AppendVBO(Buffer::VBOType::ColorBuffer, colors, sizeof(colors), offsetColor);

		offsetVertex += BYTES_PER_LINE_VERTEX;
		offsetColor += BYTES_PER_LINE_COLOR;
	}

	//==================================
	//Positive horizontal lines
	//==================================

	for (int i = 1; i < SIZE + 1; i++)
	{
		GLint vertices[] = { -SIZE, 0, 0 + i,     //first vertex
							  SIZE, 0, 0 + i };     //second vertex

		GLfloat colors[] = { 0.5f, 0.5f, 0.5f, 1.0f,
							 0.5f, 0.5f, 0.5f, 1.0f };

		m_buffer.AppendVBO(Buffer::VBOType::VertexBuffer, vertices, sizeof(vertices), offsetVertex);
		m_buffer.AppendVBO(Buffer::VBOType::ColorBuffer, colors, sizeof(colors), offsetColor);

		offsetVertex += BYTES_PER_LINE_VERTEX;
		offsetColor += BYTES_PER_LINE_COLOR;
	}

	m_position = glm::vec3(0.0f);
	m_rotation = glm::vec3(0.0f);
}

Transform& Grid::GetTransform()
{
	return m_transform;
}

void Grid::Render(const Shader& shader)
{
	shader.SendData("isTextured", false);
	shader.SendData("model", m_transform.GetMatrix());

	m_buffer.LinkVBO(shader, "vertexIn", Buffer::VBOType::VertexBuffer, Buffer::ComponentType::XYZ, Buffer::DataType::IntData);
	m_buffer.LinkVBO(shader, "colorIn", Buffer::VBOType::ColorBuffer, Buffer::ComponentType::RGBA, Buffer::DataType::FloatData);
	
	m_buffer.Render(Buffer::DrawType::Lines);
}