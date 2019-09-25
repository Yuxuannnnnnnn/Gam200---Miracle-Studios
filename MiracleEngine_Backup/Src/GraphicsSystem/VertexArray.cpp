#include "VertexArray.h"

#include <glew.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &_id);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const BufferLayout& layout)
{
	Select();
	vb.Select();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		(glEnableVertexAttribArray(i));
		(glVertexAttribPointer(i, element.count, element.type,
			element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Select() const
{
	glBindVertexArray(_id);
}

void VertexArray::UnSelect() const
{
	glBindVertexArray(0);
}
