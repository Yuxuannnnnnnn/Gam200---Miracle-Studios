#include "PrecompiledHeaders.h"
#include "IForce.h"
#include "PhysicSystem/PhysicsSystem.h"

void IForce::AddForce(size_t uId, Vector3 forceDir, float force)
{
	PhysicsSystem::AddForce(uId, forceDir, force);
}

void IForce::AddForwardForce(size_t uId, float force)
{
	PhysicsSystem::AddForwardForce(uId, force);
}
