#pragma once

#include "UIMesh.h"
#include "Shader.h"
// a class of rendering images on screen space

// font, UI image

class UIManager
{
public:
	void SceneBegin();
	void SceneEnd();
private:
	UIMesh _uiMesh;
};