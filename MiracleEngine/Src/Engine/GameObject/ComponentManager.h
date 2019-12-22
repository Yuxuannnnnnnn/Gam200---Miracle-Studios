#pragma once

#include "GameObject/Components/Graphic/AnimationComponent.h"
#include "GameObject/Components/Graphic/CameraComponent.h"
#include "GameObject/Components/Graphic/FontComponent.h"
#include "GameObject/Components/Graphic/GraphicComponent.h"
#include "GameObject/Components/Graphic/TransformComponent.h"
#include "GameObject/Components/Graphic/UIComponent.h"

#include "GameObject/Components/Logic/LogicComponent.h"

#include "GameObject/Components/Physic/BoxCollider2DComponent.h"
#include "GameObject/Components/Physic/CircleCollider2DComponent.h"
#include "GameObject/Components/Physic/EdgeCollider2DComponent.h"
#include "GameObject/Components/Physic/ICollider2D.h"
#include "GameObject/Components/Physic/RigidBody2DComponent.h"

#include "GameObject/Components/AudioComponent.h"
#include "GameObject/Components/ButtonComponent.h"
#include "GameObject/Components/IdentityComponent.h"
#include "GameObject/Components/ImGuizmoComponent.h"
#include "GameObject/Components/TileMapComponent.h"

class ComponentManager final
{
public:
	std::unordered_map < size_t, IdentityComponent* >	_IdentityComponents;	//Array of Components

	std::unordered_map <size_t, AudioComponent*>		_audioComponent;
	std::unordered_map <size_t, ButtonComponent*>		_buttonComponent;
	std::unordered_map <size_t, PickingCollider*>		_imGuizmoComponent;
	std::unordered_map <size_t, TileMapComponent*>		_TileMapComponents;

	std::unordered_map < size_t, AnimationComponent*>	_AnimationComponents;
	std::unordered_map < size_t, CameraComponent*>		_CameraComponents;
	std::unordered_map <size_t, FontComponent*>			_FontComponent;
	std::unordered_map < size_t, GraphicComponent* >	_graphicComponents;
	std::unordered_map < size_t, TransformComponent*>	_transformComponents;
	std::unordered_map < size_t, UIComponent*>			_uiComponents;
	
	std::unordered_map < size_t, LogicComponent* >		_logicComponents;

	std::unordered_map < size_t, Collider2D* >			_collider2dComponents;
	std::unordered_map < size_t, RigidBody2D* >			_rigidbody2DComponent;
};