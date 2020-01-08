#include "QuadMesh.h"
#include "PrecompiledHeaders.h"
void QuadMesh::Select()
{
	_vao->Select();
	_ebo->Select();
}

VertexBuffer* QuadMesh::GetBuffer() const
{
	return _vbo;
}

QuadMesh::QuadMesh()
{
	GLfloat _positions[] =
	{
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // 0     // bottom left
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 1     // bottom right
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // 2     // top right
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // 3     // top left
	};
	GLuint _indices[6] =
	{
		0,1,2,
		2,3,0
	};

	_vao = new VertexArray();
	BufferLayout layout;

	layout.Push<float>(3);    // 3 float position
	layout.Push<float>(2);    // 2 float UV

	_vbo = new VertexBuffer(_positions, 4 * 5 * sizeof(GLfloat)); // bind vbo, bind, ebo must bind every single loop
	_vao->AddBuffer(*_vbo, layout);
	_ebo = new ElementBuffer(_indices, 6);

}

QuadMesh::QuadMesh(float u0, float v0, float u1, float v1)
{
	GLfloat _positions[] =
	{
		-0.5f, -0.5f, 0.0f, u0, v0, // 0     // bottom left
		 0.5f, -0.5f, 0.0f, u1, v0,// 1     // bottom right
	 	 0.5f,  0.5f, 0.0f, u1, v1,// 2     // top right
		-0.5f,  0.5f, 0.0f, u0, v1 // 3     // top left
	};
	GLuint _indices[6] =
	{
		0,1,2,
		2,3,0
	};

	_vao = new VertexArray();
	BufferLayout layout;

	layout.Push<float>(3);    // 3 float position
	layout.Push<float>(2);    // 2 float UV

	_vbo = new VertexBuffer(_positions, 4 * 5 * sizeof(GLfloat)); // bind vbo, bind, ebo must bind every single loop
	_vao->AddBuffer(*_vbo, layout);
	_ebo = new ElementBuffer(_indices, 6);
	
}

QuadMesh::~QuadMesh()
{
	delete _vao;
	delete _vbo;
	delete _ebo;
}