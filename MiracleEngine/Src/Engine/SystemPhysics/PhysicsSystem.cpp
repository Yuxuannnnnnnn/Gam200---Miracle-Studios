///////////////////////////////////////////////////////////////////////////////////////
//
//	PhysicsSystem.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "PhysicsSystem.h"

void PhysicsSystem::Update(double dt)
{
	_engineSystems._rigidbodyManager->UpdateVelocity(dt);
	_engineSystems._collisionManager->Update(dt);
	_engineSystems._rigidbodyManager->ApplyVelocityToObject(dt);
}



/////////////////////////////////////////////////////

void PhysicsSystem::Draw()
{
	_engineSystems._rigidbodyManager->Draw();
	_engineSystems._collisionManager->Draw();
}