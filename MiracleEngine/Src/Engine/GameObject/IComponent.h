#pragma once
#include <string>
#include "Tools/FileIO/Serialiser.h"
#include "Tools/FileIO/DeSerialiser.h"


#ifndef ICOMPONENTSYSTEM_H
#define	ICOMPONENTSYSTEM_H


enum class ComponentId {
	IDENTITY_COMPONENT = 0,	//Compulsory Component for all GameObjects

	TRANSFORM_COMPONENT,	// 1 Graphical Components
	GRAPHICS_COMPONENT,		// 2
	ANIMATION_COMPONENT,	// 3
	CAMERA_COMPONENT,		// 4
	FONT_COMPONENT,			// 5

	RIGIDBODY_COMPONENT,	// 6 Physics Components
	CIRCLECOLLIDER_COMPONENT,//7
	BOXCOLLIDER_COMPONENT,	// 8
	EDGECOLLIDER_COMPONENT,	// 9

	LOGIC_COMPONENT,		// 10 Logic Components

	AUDIO_COMPONENT,		// 11 Audio Component
	BUTTON_COMPONENT,		// 12

	TILEMAP_COMPONENT,		// 13

	COUNTCOMPONENT,			// 14

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

	case ComponentId::BUTTON_COMPONENT:			return "ButtonComponent";
	case ComponentId::TILEMAP_COMPONENT:		return "TileMapComponent";

	default:      return "[Unknown TypeIdComponent]";
	}
}


class GameObject; // forward declaration

class IComponent
{
private:

	GameObject* _ParentPtr;
	size_t _ParentId;
	bool _enable;

public:

	IComponent();
	IComponent(GameObject * parent, size_t uId);	//Initialise Parent Ptr & ParentId
	virtual ~IComponent() = default;	//virtual destructor to delete deerived Components

//Interface functions to be implemented by Derived Classes
	virtual std::string ComponentName() const = 0; //Every Comoponent has a ComponentName function
	virtual void SerialiseComponent(Serialiser & document) = 0; //Every Component has to have a serialise function
	virtual void DeSerialiseComponent(DeSerialiser & prototypeDoc) = 0; //Every Component has to have a DeSerialise function
	virtual void Inspect() = 0;	//Every Component has an Inspect function for InspectionImguiWindow
	//virtual IComponent* CloneComponent() = 0;
	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, DeSerialiser& SceneFile) = 0;


	size_t GetParentId() const;
	void SetParentId(size_t inVal);
	GameObject* GetParentPtr();
	void SetParentPtr(GameObject* inVal);

	IComponent* GetSibilingComponent(ComponentId _componentId);

	bool GetEnable() const { return _enable; }
	void SetEnable(bool enable) { _enable = enable; }

	void DestoryThis();
};

#endif
