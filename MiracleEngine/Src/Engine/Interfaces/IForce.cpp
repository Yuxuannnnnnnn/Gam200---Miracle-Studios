#include "PrecompiledHeaders.h"
#include "IForce.h"

void IForce::AddForce(size_t uId, Vector3 forceDir, float force)
{
	_GlobalContainer._rigidbodyManager->AddForce(uId, forceDir, force);
}

void IForce::AddForwardForce(size_t uId, float force)
{
	_GlobalContainer._rigidbodyManager->AddForwardForce(uId, force);
}
