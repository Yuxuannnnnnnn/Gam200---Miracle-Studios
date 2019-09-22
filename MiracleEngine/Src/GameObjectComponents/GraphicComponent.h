#pragma once
#include <MathLib/Vector3.h>
#include "IComponentSystem.h"
#include "../GraphicsSystem/MeshManager.h"


class GraphicComponent : public IComponentSystem
{
private:
	
	int _shaderID;
	int _textureID;
	Mesh* _pmesh;

	// bool transparent.. so on
	//Store the vb, ib, vao, shader

public:
	GraphicComponent();

	GraphicComponent()
		: _shaderID{0},
		  _textureID{0},
		_pmesh{ new QuadMesh()}
	{
	}
	
	std::string ComponentName() const override
	{
		return "Graphic Component";
	}

	~GraphicComponent()
	{
		delete _pmesh;
	}
};

