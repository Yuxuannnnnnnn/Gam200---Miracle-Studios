///////////////////////////////////////////////////////////////////////////////////////
//
//	Collider2D.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _COLLIDER_2D_H
#define _COLLIDER_2D_H

#include "GameObjectComponents/IComponentSystem.h"
#include "../GraphicComponents/TransformComponent.h"
#include "RigidBody2D.h"
#include "GraphicsSystem/DebugRenderer.h"

#include "MathLib/SYMath.h"

enum class ColliderType{
    
    NONE_COLLIDER = 0,
    BOX_COLLIDER = 1,
    CIRCLE_COLLIDER = 2,
	LINE_COLLIDER = 3,

  };

class Collider2D : public IComponentSystem
{
public:
	unsigned _type;
	unsigned _layer;

	bool _attachedRigidboy;

	bool _enable;
	bool _trigger;

protected:
	TransformComponent* _transform;
	RigidBody2D* _rigidbody;

public:
	Collider2D(GameObject* parent, size_t uId, IComponentSystem* component = nullptr);

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void Inspect() override;

	// Constructor
	Collider2D(TransformComponent* transform = nullptr) :
		_type{ (unsigned)ColliderType::NONE_COLLIDER },
		_layer{ 0 },
		_attachedRigidboy{ false },
		_enable{ true },
		_trigger{ true },
		_transform{ transform },
		_rigidbody{ nullptr }
	{
	}

	Collider2D(const Collider2D& rhs);

	virtual ~Collider2D() {}

	//No replication of class object
	Collider2D& operator= (const Collider2D& rhs) = delete;

	virtual void Draw() {};
	virtual void Update() {};


	TransformComponent* GetTransform() const
	{
		return _transform;
	}

	RigidBody2D* GetRigidbody() const
	{
		return _rigidbody;
	}
	
};

#endif
