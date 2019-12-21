#pragma once
#include "QuadMesh.h"
#include "Shader.h"

// basic non-batch renderer

class BasicRenderer
{


public:
	void SceneBegin();
	void SceneEnd();
private:
	QuadMesh _quadMesh;
	
};