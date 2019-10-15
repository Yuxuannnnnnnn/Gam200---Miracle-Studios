#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Elementbuffer.h"
#include "BufferLayout.h"
#include "Texture2D.h"

class QuadMesh
{
public:
	void Select();
	QuadMesh();
	~QuadMesh();
private:
	VertexArray* _vao;
	VertexBuffer* _vbo;
	ElementBuffer* _ebo;
	//Texture2D* _texture;
};