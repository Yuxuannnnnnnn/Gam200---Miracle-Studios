#pragma once

#include <vector>

class BatchRenderer
{
public:
	std::vector<float> _verts;
	void PushBackVertex(const glm::vec3& vertex);

	bool IsEmpty() const;
	void ClearBuffer();

	size_t GetVertexCount() const;
	size_t GetElementCount() const;

	std::vector<float> _vert;

private:

	// number of vertices
	size_t _count;
};