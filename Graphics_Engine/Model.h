#pragma once

#include <string>
#include <vector>
#include "Buffer.h"
#include "Material.h"
#include "Object.h"

struct Mesh
{
	std::string name;
	std::string materialName;

	std::vector<GLuint> indices;
	std::vector<glm::vec4> colors;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> textureCoords;
};

struct VertexGroup
{
	int v = -1;
	int t = -1;
	int n = -1;

	bool operator==(const VertexGroup& other) const
	{
		return (v == other.v && t == other.t && n == other.n);
	}
};

typedef std::vector<VertexGroup> Face;

class HashFunction
{

public:

	size_t operator()(const VertexGroup& v) const
	{
		return v.v + v.t + v.n;
	}
};

class Model : public Object
{

public:

	Model(const std::string& filename, Grid* parentGrid = nullptr);

	void Update() override {}
	void Render(const Shader& shader) override;
	void SetColor(const glm::vec4& color) override;

private:

	void FillBuffers();
	void SortVertexData(Mesh& newMesh, const Mesh& oldMesh,
		const std::vector<Face>& faces);

	std::vector<Mesh> m_meshes;
	std::vector<Buffer> m_buffers;
	std::vector<Material> m_materials;

};