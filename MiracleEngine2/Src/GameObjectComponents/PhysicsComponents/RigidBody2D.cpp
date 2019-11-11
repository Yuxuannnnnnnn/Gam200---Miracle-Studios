///////////////////////////////////////////////////////////////////////////////////////
//
//	RigidBody2D.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "RigidBody2D.h"
#include "GraphicsSystem/DebugRenderer.h"


RigidBody2D::RigidBody2D(GameObject* parent, size_t uId, IComponentSystem* component)
	:IComponentSystem(parent, uId),
	_velocity{},
	_appliedForce{},
	_direction{ 1.f,0.f,0.f },
	_mass{ 1.f },
	_fictionVal{ 0.f },
	_static{ true }
{

	if (component)
	{
		RigidBody2D* rigidBodyComponent = dynamic_cast<RigidBody2D*>(component);
		_velocity = rigidBodyComponent->_velocity;
		_direction = rigidBodyComponent->_direction;
		_appliedForce = rigidBodyComponent->_appliedForce;
		_mass = rigidBodyComponent->_mass;
		_fictionVal = rigidBodyComponent->_fictionVal;
		_static = rigidBodyComponent->_static;
	}
}

std::string RigidBody2D::ComponentName() const
{
	return std::string("RigidBody Component");
}


void RigidBody2D::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Mass") && document["Mass"].IsFloat())	//Checks if the variable exists in .Json file
		_mass = document["Mass"].GetFloat();

	if (document.HasMember("Friction") && document["Friction"].IsFloat())
		_fictionVal = document["Friction"].GetFloat();

	if (document.HasMember("Static") && document["Static"].IsBool())
		_static = document["Static"].GetBool();

}

void RigidBody2D::Inspect()
{
	IComponentSystem::Inspect();

	ImGui::Spacing();
	ImGui::Checkbox("Static", &_static);

	ImGui::Spacing();
	ImGui::InputFloat3("Velocity X, Y, Z", _velocity.m);

	ImGui::Spacing();
	ImGui::InputFloat3("Direction X, Y, Z", _direction.m);

	ImGui::Spacing();
	ImGui::InputFloat3("Applied Force X, Y, Z", _appliedForce.m);

	ImGui::Spacing();
	ImGui::InputFloat("Mass", &_mass);

	ImGui::Spacing();
	ImGui::InputFloat("Friction Value", &_fictionVal);

	ImGui::Spacing();

}


RigidBody2D::RigidBody2D(TransformComponent* transform) :
	_velocity{},
	_appliedForce{},
	_direction{ 0.f,1.f,0.f },
	_mass{ 1.f },
	_fictionVal{ 0.f },
	_static{ true },
	_componentEnable{ true },
	_transform{ transform }
{
}

RigidBody2D::RigidBody2D(const RigidBody2D& rhs) :
	_velocity{ rhs ._velocity },
	_appliedForce{ rhs._appliedForce },
	_direction{ rhs._direction },
	_mass{ rhs._mass },
	_fictionVal{ rhs._fictionVal },
	_static{ rhs._static },
	_componentEnable{ rhs._componentEnable },
	_transform{ nullptr }
{
}

void RigidBody2D::UpdateVec(double dt)
{
	if (_static)
		return;

	Vector3 newVel{ 0.f, 0.f , 0.f};

	// newVel = a * dt + currVel;;
	newVel = _appliedForce / _mass;
	newVel = _velocity + newVel * (float)dt;

	// newVel = newVel * firction;
	newVel = newVel * (1.f - _fictionVal);

	_velocity = newVel;

	_appliedForce = Vector3{ 0.f,0.f,0.f };

	Draw();

}

void RigidBody2D::UpdatePos(double dt)
{
	if (_static)
		return;

	// newPos = newVel * dt + currPos;
	_transform->GetPos() += _velocity * (float)dt;
}

void RigidBody2D::Draw()
{
	Vector3 newVel = _velocity.Normalized();
	float length = _velocity.SquaredLength();

	if (length > 50.f)
		length = 50.f;

	DebugRenderer::GetInstance().DrawLine(_transform->GetPos()._x, _transform->GetPos()._y, _transform->GetPos()._x + newVel._x * length, _transform->GetPos()._y + newVel._y * length);
}

void RigidBody2D::StopVelocity()
{
	_velocity = Vector3::Vec3Zero;
}

void RigidBody2D::AddForce(Vector3 forceDir, float force)
{
	forceDir.Normalize();
	_appliedForce += forceDir * force;
}

void RigidBody2D::AddForwardForce(float force)
{
	Mtx33 temp = Mtx33::CreateRotation(_transform->GetRotate());

	Vector2 result = temp * Vector2{ 0, 1 };
	_direction.Set(result._x, result._y);
	_direction.Normalize();

	_appliedForce += _direction * force;
}

void RigidBody2D::SetFiction(float value)
{
	_fictionVal = value;
}

void RigidBody2D::SetMass(float mass)
{
	_mass = mass;
}

void RigidBody2D::SetType(bool type)
{
	_static = type;
}