#include "QuadMesh.h"
#include "PrecompiledHeaders.h"
void QuadMesh::Select()
{
	_vao->Select();
	_ebo->Select();
	//_texture->Select();
}
QuadMesh::QuadMesh()
{
	GLfloat _positions[] =
	{
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // 0// 0
		0.5f , -0.5f, 0.0f,1.0f, 0.0f, // 1// 1
		0.5f , 0.5f,  0.0f,1.0f , 1.0f, // 2// 2
		-0.5f, 0.5f, 0.0f,0.0f, 1.0f  // 3// 3  
	};
	GLuint _indices[6] =
	{
		0,1,2,
		2,3,0
	};

	_vao = new VertexArray();
	BufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);

	_vbo = new VertexBuffer(_positions, 4 * 5 * sizeof(GLfloat)); // bind vbo, bind, ebo must bind every single loop
	_vao->AddBuffer(*_vbo, layout);
	_ebo = new ElementBuffer(_indices, 6);
	//_texture = new Texture2D("zombie.png");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

QuadMesh::~QuadMesh()
{
	delete _vao;
	delete _vbo;
	delete _ebo;
	//delete _texture;
}