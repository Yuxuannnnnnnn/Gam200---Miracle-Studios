#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Elementbuffer.h"
#include "BufferLayout.h"
#include "Texture2D.h"
#include "Animations.h"

class PlayerMesh
{
public:
	void Select(double dt, int num);
	PlayerMesh();
private:
	VertexArray* _vao;
	Animations* _vbo;
	ElementBuffer* _ebo;
	Texture2D* _texture[3];
};