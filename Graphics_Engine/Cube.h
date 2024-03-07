#pragma once

#include <string>
#include "Buffer.h"
#include "Material.h"
#include "Object.h"
#include "Texture.h"

class Cube : public Object
{

public:

	Cube(const std::string& textureFilename, Grid* parentGrid = nullptr);
	~Cube() override;

	void SetColor(const glm::vec4& color) override;

	void Update() override {}
	void Render(const Shader& shader) override;

private:

	Buffer m_buffer;
	Texture m_texture;
	Material m_material;

};