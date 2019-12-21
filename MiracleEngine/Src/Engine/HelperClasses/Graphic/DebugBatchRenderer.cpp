#include "PrecompiledHeaders.h"
#include "DebugBatchRenderer.h"

void DebugBatchRenderer::PushBackVertex(const glm::vec3& vertex)
{
	vert.push_back(vertex.x);
	vert.push_back(vertex.y);
	vert.push_back(vertex.z);

	++_count;
}


bool DebugBatchRenderer::IsEmpty() const
{
	return (bool)_count;
}

void DebugBatchRenderer::ClearBuffer()
{
	vert.clear();
}

size_t DebugBatchRenderer::GetVertexCount() const
{
	return vert.size() / 3;
}

size_t DebugBatchRenderer::GetElementCount() const
{
	return vert.size();
}