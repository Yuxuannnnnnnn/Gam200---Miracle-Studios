#pragma once
#include <string>
#include "Tools/FileIO/Serialiser.h"


#ifndef ICOMPONENTSYSTEM_H
#define	ICOMPONENTSYSTEM_H


enum class ComponentId {
	IDENTITY_COMPONENT = 0,	//Compulsory Component for all GameObjects

	TRANSFORM_COMPONENT,	//Graphical Components
	GRAPHICS_COMPONENT,		//
	ANIMATION_COMPONENT,	//
	CAMERA_COMPONENT,		//
	FONT_COMPONENT,			//

	RIGIDBODY_COMPONENT,	//Physics Components
	CIRCLECOLLIDER_COMPONENT,
	BOXCOLLIDER_COMPONENT,
	EDGECOLLIDER_COMPONENT,

	LOGIC_COMPONENT,		//Logic Components

	AUDIO_COMPONENT,	//Audio Component
	COUNTCOMPONENT
};

inline const char* ToString(ComponentId type) //Convert TypeIdComponent Enum to const char* - For Use only in Imgui
{
	switch (type)
	{
	case ComponentId::IDENTITY_COMPONENT:		return "IdentityComponent";
		 
	case ComponentId::TRANSFORM_COMPONENT:		return "TransformComponent";
	case ComponentId::GRAPHICS_COMPONENT: 		return "GraphicsComponent";
	case ComponentId::ANIMATION_COMPONENT:		return "AnimationComponent";
	case ComponentId::CAMERA_COMPONENT: 		return "CameraComponent";
	case ComponentId::FONT_COMPONENT: 			return "FontComponent";
		 
	case ComponentId::RIGIDBODY_COMPONENT:		return "RigidBodyComponent";
	case ComponentId::CIRCLECOLLIDER_COMPONENT: return "CircleColliderComponent";
	case ComponentId::BOXCOLLIDER_COMPONENT:	return "BoxColliderComponent";
	case ComponentId::EDGECOLLIDER_COMPONENT:	return "EdgeColliderComponent";
		 
	case ComponentId::LOGIC_COMPONENT:			return "LogicComponent";
		 
	case ComponentId::AUDIO_COMPONENT:			return "AudioComponent";

	default:      return "[Unknown TypeIdComponent]";
	}
}


class GameObject; // forward declaration

class IComponentSystem
{
private:

	GameObject* _ParentPtr;
	size_t _ParentId;
	bool _enable;

public:

	IComponentSystem();
	IComponentSystem(GameObject * parent, size_t uId);	//Initialise Parent Ptr & ParentId
	virtual ~IComponentSystem() = default;	//virtual destructor to delete deerived Components

//Interface functions to be implemented by Derived Classes
	virtual std::string ComponentName() const = 0; //Ever Comoponent has a ComponentName function
	virtual void SerialiseComponent(Serialiser & document) = 0; //Every Component has to have a serialise function
	virtual void Inspect() = 0;	//Every Component has an Inspect function for InspectionImguiWindow

	size_t GetParentId() const;
	void SetParentId(size_t inVal);
	GameObject* GetParentPtr();
	void SetParentPtr(GameObject* inVal);

	IComponentSystem* GetSibilingComponent(unsigned _componentId);

	bool GetEnable() const { return _enable; }
	void SetEnable(bool enable) { _enable = enable; }

	void DestoryThis();
};

#endif
