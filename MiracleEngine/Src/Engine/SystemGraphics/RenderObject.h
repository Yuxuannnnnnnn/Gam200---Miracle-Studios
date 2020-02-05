#pragma once

#include "Texture2D.h"
#include "Shader.h"
#include "QuadMesh.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"



struct UV
{
	float u0 = 0.0f;
	float v0 = 0.0f;
	float u1 = 1.0f;
	float v1 = 1.0f;
};

enum RENDERCURRENT
{
	RENDERNONE,
	STATIC,
	ANIMATED
};

struct RenderObject
{
	Texture2D* _pTexture;
	Shader*    _pShader;
	QuadMesh*  _pMesh;
	glm::mat4  _transform;
	UV  _uv;
	float _zvalue;
	bool _isAnimated;
	float _alpha;

};