#include "glew.h"


class VertexBuffer
{
private:

	GLuint _rendererID;

public:

	VertexBuffer(GLfloat* data, size_t size);
	~VertexBuffer();

	void Bind();
	void Unbind();

};