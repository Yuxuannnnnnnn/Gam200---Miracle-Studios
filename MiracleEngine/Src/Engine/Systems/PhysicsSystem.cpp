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
#include "GlobalContainer.h"

void PhysicsSystem::Update(double dt)
{
	_GlobalContainer._rigidbodyManager->UpdateVelocity(dt);
	_GlobalContainer._collisionManager->Update(dt);
	_GlobalContainer._rigidbodyManager->ApplyVelocityToObject(dt);
}



/////////////////////////////////////////////////////

void PhysicsSystem::Draw()
{
	_GlobalContainer._rigidbodyManager->Draw();
	_GlobalContainer._collisionManager->Draw();
}

