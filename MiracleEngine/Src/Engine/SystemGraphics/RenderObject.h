#pragma once

#include "Texture2D.h"
#include "Shader.h"
#include "QuadMesh.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct RenderObject
{
	Texture2D* _pTexture;
	Shader*    _pShader;
	QuadMesh*  _pMesh;
	glm::mat4  transform;
};