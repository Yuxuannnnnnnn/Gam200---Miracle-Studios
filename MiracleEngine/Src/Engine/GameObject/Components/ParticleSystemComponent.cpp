#include "PrecompiledHeaders.h"
#include "ParticleSystemComponent.h"

std::string ParticleSystemComponent::ComponentName() const
{
	return "ParticleSystemComponent";
}
void ParticleSystemComponent::SerialiseComponent(Serialiser& document)
{
	(void)document;
}
void ParticleSystemComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	(void)prototypeDoc;
}

void ParticleSystemComponent::Inspect()
{

}

//Constructor
ParticleSystemComponent::ParticleSystemComponent() :
	_startAmount{0},
	_limitAmount{0},
	_releaseAmount{0},
	_Lifetime{0.f},
	_loop{false},
	_startCreation{false},
	_particleSprite{"default.png"},
	_particleShader{"defaultGraphic"},
	_particleOrigin{},
	_particleStartScale{},
	_particleGrowRate{},
	_particleLimitScale{},
	_particleRotation{0.f},
	_particleInitialVel{},
	_particleForce{},
	_particleAccel{},
	_particleLifetime{0.f}
{

}
ParticleSystemComponent::~ParticleSystemComponent()
{

}
