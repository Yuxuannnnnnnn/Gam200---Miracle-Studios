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
//#include "GraphicsSystem/DebugRenderer.h"

RigidBody2D::RigidBody2D() :
	_velocity{},
	_appliedForce{},
	_direction{ 1.f,0.f,0.f },
	_angle{ 0.f },
	_mass{ 1.f },
	_fictionVal{ 0.f },
	_static{ true }

{
}

void RigidBody2D::UpdateVec(double dt)
{
	if (_static)
		return;

	Vector3 newVel{ 0.f, 0.f , 0.f};

	// newVel = a * dt + currVel;;
	newVel = _appliedForce * (float)dt;
	newVel += _velocity;

	// newVel = newVel * firction;
	newVel = newVel * (1.f - _fictionVal);

	_velocity = newVel;

	_appliedForce = Vector3{ 0.f,0.f,0.f };

	Draw();
}

void RigidBody2D::UpdatePos(double dt)
{
	// newPos = newVel * dt + currPos;
	//_gameObject->_pos += _velocity * (float)dt;
}

void RigidBody2D::Draw()
{
	Vector3 newVel = _velocity.Normalized();
	float length = _velocity.SquaredLength();

	if (length > 100.f)
		length = 100.f;

	//DebugRenderer::GetInstance().DrawLine(_gameObject->_pos._x, _gameObject->_pos._y, _gameObject->_pos._x + newVel._x * length, _gameObject->_pos._y + newVel._y * length);
}