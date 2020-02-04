#include "PrecompiledHeaders.h"
#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem()
{
}

void PhysicsSystem::Update(double dt)
{
	UpdateVelocity(dt);
	CollisionUpdate(dt);
	ApplyVelocityToObject(dt);
}

void PhysicsSystem::Draw()
{
	RigidbodyDraw();
	AllColliderDraw();	
}