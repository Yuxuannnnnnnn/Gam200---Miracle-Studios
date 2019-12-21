#include "PrecompiledHeaders.h"
#include "BatchRenderer.h"

void BatchRenderer::PushBackVertex(const glm::vec3& vertex)
{
	_vert.push_back(vertex.x);
	_vert.push_back(vertex.y);
	_vert.push_back(vertex.z);

	++_count;
}


bool BatchRenderer::IsEmpty() const
{
	return (bool)_count;
}

void BatchRenderer::ClearBuffer()
{
	_vert.clear();
}

size_t BatchRenderer::GetVertexCount() const
{
	return _vert.size() / 3;
}

size_t BatchRenderer::GetElementCount() const
{
	return _vert.size();
}