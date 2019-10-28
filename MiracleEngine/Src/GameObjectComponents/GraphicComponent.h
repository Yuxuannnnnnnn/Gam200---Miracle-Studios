#pragma once
#include "IComponentSystem.h"
#include "GraphicsSystem/MeshManager.h"

enum class TypeIdGraphic {
	NONE = 0,

};

class GraphicComponent : public IComponentSystem
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


		TransformComponent* tempTrans = (TransformComponent*)
			GetSibilingComponent((unsigned)TypeIdSiblingComp::TRANSFORMCOMPONENT);
		if (tempTrans)
		{
			std::cout
				<< "/tSibling Trans"
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

		//LogicComponent* tempLogic = nullptr;// = (LogicComponent*)
			//GetSibilingComponent((unsigned)TypeIdSiblingComp::LOGICCOMPONENT);
		//if (tempRigid)
		//{
		//	std::cout
		//		<< "/tSibling Logic"
		//		<< tempLogic->GetHealth()
		//		<< tempLogic->GetLifetime()
		//		<< tempLogic->GetSpeed()
		//		<< std::endl;
		//}
	}
};

