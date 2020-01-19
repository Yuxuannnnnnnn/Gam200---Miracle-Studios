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

	CT_DataMove, // DataMove
	CT_DataTransform,
	CT_DataPlayer,
	CT_DataHealth,

	CT_Particle,
	CT_ParticleSystem,

	CT_UI,

	CT_Count,
	
	CT_ERROR
};

inline const char* ToRegisterID(ComponentId type)
{
	switch (type)
	{
	case ComponentId::CT_Identity:			return "Identity";

	case ComponentId::CT_Transform:			return "Transform";
	case ComponentId::CT_Graphic: 			return "Graphic";
	case ComponentId::CT_Animation:			return "Animation";
	case ComponentId::CT_Camera: 			return "Camera";
	case ComponentId::CT_Font: 				return "Font";

	case ComponentId::CT_RigidBody2D:		return "RigidBody2D";
	case ComponentId::CT_CircleCollider2D:	return "CircleCollider2D";
	case ComponentId::CT_BoxCollider2D:		return "BoxCollider2D";
	case ComponentId::CT_EdgeCollider2D:	return "EdgeCollider2D";

	case ComponentId::CT_Logic:				return "Logic";

	case ComponentId::CT_Audio:				return "Audio";

	case ComponentId::CT_Button:			return "Button";
	case ComponentId::CT_TileMap:			return "TileMap";

	case ComponentId::CT_DataMove:			return "DataMove";
	case ComponentId::CT_DataTransform:		return "DataTransform";
	case ComponentId::CT_DataPlayer:		return "DataPlayer";
	case ComponentId::CT_DataHealth:		return "DataHealth";

	case ComponentId::CT_Particle:			return "Particle";
	case ComponentId::CT_ParticleSystem:	return "ParticleSystem";

	case ComponentId::CT_UI:		return "UI";

	default:      return "None";
	}
}

inline const char* ToString(ComponentId type) //Convert TypeIdComponent Enum to const char* - For Use only in Imgui
{
	switch (type)
	{
	case ComponentId::CT_Identity:			return "IdentityComponent";

	case ComponentId::CT_Transform:			return "TransformComponent";
	case ComponentId::CT_Graphic: 			return "GraphicsComponent";
	case ComponentId::CT_Animation:			return "AnimationComponent";
	case ComponentId::CT_Camera: 			return "CameraComponent";
	case ComponentId::CT_Font: 				return "FontComponent";

	case ComponentId::CT_RigidBody2D:		return "RigidBodyComponent";
	case ComponentId::CT_CircleCollider2D:	return "CircleColliderComponent";
	case ComponentId::CT_BoxCollider2D:		return "BoxColliderComponent";
	case ComponentId::CT_EdgeCollider2D:	return "EdgeColliderComponent";

	case ComponentId::CT_Logic:				return "LogicComponent";

	case ComponentId::CT_Audio:				return "AudioComponent";

	case ComponentId::CT_Button:			return "ButtonComponent";
	case ComponentId::CT_TileMap:			return "TileMapComponent";

	case ComponentId::CT_DataMove:			return "DataMoveComponent";
	case ComponentId::CT_DataTransform:		return "DataTransformComponent";
	case ComponentId::CT_DataPlayer:		return "DataPlayerComponent";
	case ComponentId::CT_DataHealth:		return "DataHealthComponent";
	
	case ComponentId::CT_Particle:			return "ParticleComponent";
	case ComponentId::CT_ParticleSystem:	return "ParticleSystemComponent";

	case ComponentId::CT_UI:		return "UIComponent";

	default:      return "[Unknown TypeIdComponent]";
	}
}

inline ComponentId ToComponentID(const std::string& type)
{
	if (type.compare("Transform") == 0)
		return ComponentId::CT_Transform;
	if (type.compare("TransformComponent") == 0)
		return ComponentId::CT_Transform;

	if (type.compare("DataMove") == 0)
		return ComponentId::CT_DataMove;
	if (type.compare("DataMoveComponent") == 0)
		return ComponentId::CT_DataMove;

	if (type.compare("DataTransform") == 0)
		return ComponentId::CT_DataTransform;
	if (type.compare("DataTransformComponent") == 0)
		return ComponentId::CT_DataTransform;

	if (type.compare("DataPlayer") == 0)
		return ComponentId::CT_DataPlayer;
	if (type.compare("DataPlayerComponent") == 0)
		return ComponentId::CT_DataPlayer;

	if (type.compare("DataHealth") == 0)
		return ComponentId::CT_DataHealth;
	if (type.compare("DataHealthComponent") == 0)
		return ComponentId::CT_DataHealth;

	return ComponentId::CT_ERROR;
}