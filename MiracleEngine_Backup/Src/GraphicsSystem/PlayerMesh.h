#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Elementbuffer.h"
#include "BufferLayout.h"
#include "Texture2D.h"

class PlayerMesh
{
public:
	void Select(float dt, int num)
	{
		_vao->Select();
		_ebo->Select();
		_texture[num]->Select();
		_vbo->Select(dt);
	}
	PlayerMesh()
	{
		GLfloat _positions[] =
		{
			//-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // 0// 0
			//0.5f , -0.5f, 0.0f, 1.0f / 12, 0.0f, // 1// 1
			//0.5f , 0.5f,  0.0f, 1.0f / 12, 1.0f, // 2// 2
			//-0.5f, 0.5f, 0.0f, 0.0f, 1.0f  // 3// 3  
			-0.5f, -0.5f, 0.0f, 2.0f / 12, 0.0f, // 0// 0
			0.5f , -0.5f, 0.0f, 3.0f / 12, 0.0f, // 1// 1
			0.5f , 0.5f,  0.0f, 3.0f / 12, 1.0f, // 2// 2
			-0.5f, 0.5f, 0.0f, 2.0f / 12, 1.0f  // 3// 3  
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

		_vbo = new Animation(_positions, 4 * 5 * sizeof(GLfloat)); // bind vbo, bind, ebo must bind every single loop
		_vao->AddBuffer(*_vbo, layout);
		_ebo = new ElementBuffer(_indices, 6);
		_texture[0] = new Texture2D("Image/catidle.png");
		_texture[1] = new Texture2D("Image/catrun.png");
		_texture[2] = new Texture2D("Image/catjump.png");
		(glEnable(GL_BLEND));
		(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}
private:
	VertexArray* _vao;
	Animation* _vbo;
	ElementBuffer* _ebo;
	Texture2D* _texture[3];
};