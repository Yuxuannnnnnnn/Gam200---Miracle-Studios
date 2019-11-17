#pragma once

#include <string>
#include "Tools/FileIO/Serialiser.h"

#ifndef ICOMPONENTSYSTEM_H
#define	ICOMPONENTSYSTEM_H

enum class TypeIdComponent {
	IDENTITYCOMPONENT = 0,	//Compulsory Component for all GameObjects

	TRANSFORMCOMPONENT,	//Graphical Components
	GRAPHICSCOMPONENT,	//
	ANIMATIONCOMPONENT,	//
	CAMERACOMPONENT,	//

	RIGIDBODYCOMPONENT,	//Physics Components
	COLLIDERCOMPONENT,	//
	CIRCLECOLLIDER_COMPONENT,
	BOXCOLLIDER_COMPONENT,
	EDGECOLLIDER_COMPONENT,

	AICOMPONENT,		//Logic Components
	LOGICCOMPONENT,		//

	AUDIOCOMPONENT,	//Audio Component
	COUNTCOMPONENT
};


inline const char* ToString(TypeIdComponent type) //Convert TypeIdComponent Enum to const char* - For Use only in Imgui
{
	switch (type)
	{
	case TypeIdComponent::IDENTITYCOMPONENT:	return "IdentityComponent";

	case TypeIdComponent::TRANSFORMCOMPONENT:	return "TransformComponent";
	case TypeIdComponent::GRAPHICSCOMPONENT: 	return "GraphicsComponent";
	case TypeIdComponent::ANIMATIONCOMPONENT: 	return "AnimationComponent";
	case TypeIdComponent::CAMERACOMPONENT: 		return "CameraComponent";

	case TypeIdComponent::RIGIDBODYCOMPONENT:	return "RigidBoodyComponent";
	case TypeIdComponent::COLLIDERCOMPONENT: 	return "ColliderComponent";
	case TypeIdComponent::CIRCLECOLLIDER_COMPONENT: return "CircleColliderComponent";
	case TypeIdComponent::BOXCOLLIDER_COMPONENT:	return "BoxColliderComponent";
	case TypeIdComponent::EDGECOLLIDER_COMPONENT:	return "EdgeColliderComponent";
		
	case TypeIdComponent::LOGICCOMPONENT:		return "LogicComponent";
	case TypeIdComponent::AICOMPONENT:			return "AIComponent";

	case TypeIdComponent::AUDIOCOMPONENT:		return "AudioComponent";

	default:      return "[Unknown TypeIdComponent]";
	}
}

class GameObject; //forward declaration

//IComponentSystem only contains non-editable variables
class IComponentSystem
{
private:

	GameObject* _ParentPtr; //Pointer to the GameObject this Component belongs to
	size_t _ParentId;	//Game Object Unique Id

public:
	IComponentSystem() = default;
	IComponentSystem(GameObject* parent, size_t uId);	//Initialise Parent Ptr & ParentId
	virtual ~IComponentSystem() = default;	//virtual destructor to delete deerived Components

//Interface functions to be implemented by Derived Classes
	virtual std::string ComponentName() const = 0; //Ever Comoponent has a ComponentName function
	virtual void SerialiseComponent(Serialiser& document) = 0; //Every Component has to have a serialise function
	virtual void Inspect() = 0;	//Every Component has an Inspect function for InspectionImguiWindow


	size_t GetParentId() const;	 //Get pointer to the GameObject Unique Id
	//void SetParentId(size_t inVal);
	GameObject* GetParentPtr(); //Get pointer to the GameObject Parent
	//void SetParentPtr(GameObject* inVal);

	IComponentSystem* GetSibilingComponent(unsigned _componentId);	//Get pointer to the Any of its Sibling Component based on Component Enum
};

#endif
