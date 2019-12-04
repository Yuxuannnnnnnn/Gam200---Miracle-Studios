#pragma once
#include "QuadMesh.h"

// basic non-batch renderer

class BasicRenderer
{


public:
	void SceneBegin();
	void SceneEnd();
private:
	QuadMesh _quadMesh;
	
};