#pragma once
#include "IComponentSystem.h"
#include "GraphicsSystem/MeshManager.h"

enum class TypeIdGraphic {
	NONE = 0,

};

class GraphicComponent : public IComponentSystem
{
private:
	TypeIdGraphic _typeIdGraphic;
	std::string _fileName;

	int _shaderID;
	int _textureID;
	Mesh* _pmesh;

	// bool transparent.. so on
	//Store the vb, ib, vao, shader

public:
	GraphicComponent();
	~GraphicComponent();

	std::string ComponentName() const override;
};

