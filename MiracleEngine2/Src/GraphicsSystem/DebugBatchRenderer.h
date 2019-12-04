#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class DebugBatchRenderer
{
public:
	void PushBackVertex(const glm::vec3& vertex);

	bool IsEmpty() const;
	void ClearBuffer();

	size_t GetVertexCount() const;
	size_t GetElementCount() const;
	std::vector<float> vert;

private:

	// number of vertices
	size_t _count;
};