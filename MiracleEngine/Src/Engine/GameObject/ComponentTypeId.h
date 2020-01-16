#pragma once

enum class ComponentId {
	CT_Identity = 0,	//Compulsory Component for all GameObjects

	CT_Transform,	//Graphical Components
	CT_Graphic,		//
	CT_Animation,	//
	CT_Camera,		//
	CT_Font,			//

	CT_RigidBody2D,	//Physics Components
	CT_CircleCollider2D,
	CT_BoxCollider2D,
	CT_EdgeCollider2D,

	CT_Logic,		//Logic Components

	CT_Audio,	//Audio Component
	CT_Button,

	CT_TileMap,

	CT_Count
};

inline const char* ToRegisterID(ComponentId type)
{
	switch (type)
	{
	case ComponentId::CT_Identity:		return "Identity";

	case ComponentId::CT_Transform:		return "Transform";
	case ComponentId::CT_Graphic: 		return "Graphic";
	case ComponentId::CT_Animation:		return "Animation";
	case ComponentId::CT_Camera: 		return "Camera";
	case ComponentId::CT_Font: 			return "Font";

	case ComponentId::CT_RigidBody2D:		return "RigidBody2D";
	case ComponentId::CT_CircleCollider2D: return "CircleCollider2D";
	case ComponentId::CT_BoxCollider2D:	return "BoxCollider2D";
	case ComponentId::CT_EdgeCollider2D:	return "EdgeCollider2D";

	case ComponentId::CT_Logic:			return "Logic";

	case ComponentId::CT_Audio:			return "Audio";

	case ComponentId::CT_Button:			return "Button";
	case ComponentId::CT_TileMap:		return "TileMap";

	default:      return "None";
	}
}

inline const char* ToString(ComponentId type) //Convert TypeIdComponent Enum to const char* - For Use only in Imgui
{
	switch (type)
	{
	case ComponentId::CT_Identity:		return "IdentityComponent";

	case ComponentId::CT_Transform:		return "TransformComponent";
	case ComponentId::CT_Graphic: 		return "GraphicsComponent";
	case ComponentId::CT_Animation:		return "AnimationComponent";
	case ComponentId::CT_Camera: 		return "CameraComponent";
	case ComponentId::CT_Font: 			return "FontComponent";

	case ComponentId::CT_RigidBody2D:		return "RigidBodyComponent";
	case ComponentId::CT_CircleCollider2D: return "CircleColliderComponent";
	case ComponentId::CT_BoxCollider2D:	return "BoxColliderComponent";
	case ComponentId::CT_EdgeCollider2D:	return "EdgeColliderComponent";

	case ComponentId::CT_Logic:			return "LogicComponent";

	case ComponentId::CT_Audio:			return "AudioComponent";

	case ComponentId::CT_Button:			return "ButtonComponent";
	case ComponentId::CT_TileMap:		return "TileMapComponent";

	default:      return "[Unknown TypeIdComponent]";
	}
}