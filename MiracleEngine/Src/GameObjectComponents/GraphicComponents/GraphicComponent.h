#pragma once
#include "GameObjectComponents/IComponentSystem.h"
#include "GraphicsSystem/MeshManager.h"
#include "GameObjectComponents/IBase.h"

enum class TypeIdGraphic {
	NONE = 0,

};

class GraphicComponent : public IComponentSystem, public IBase<GraphicComponent>
{
private:
	unsigned _typeIdGraphic;
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

	unsigned& GetTypeId()
	{
		return _typeIdGraphic;
	}
	std::string& GetFileName()
	{
		return _fileName;
	}

	// function to get transform component
	void TEST_getTransform()
	{
		//std::unordered_map < unsigned, IComponentSystem* > a
		//	= ChildGetCompList(_ParentPtr);
		//TransformComponent* temp = (TransformComponent * )a[0];

		// 
		TransformComponent* tempTrans = (TransformComponent*)
			GetSibilingComponent((unsigned)TypeIdComponent::TRANSFORMCOMPONENT);
		if (tempTrans)
		{
			std::cout
				<< "\tSibling Trans"
				<< tempTrans->GetPos()._x << ","
				<< tempTrans->GetPos()._y << ","
				<< tempTrans->GetPos()._z << ","
				<< " "
				<< tempTrans->GetScale()._x << ","
				<< tempTrans->GetScale()._y << ","
				<< tempTrans->GetScale()._z << ","
				<< " "
				<< tempTrans->GetRotate()
				<< std::endl;			
		}
	}
};

