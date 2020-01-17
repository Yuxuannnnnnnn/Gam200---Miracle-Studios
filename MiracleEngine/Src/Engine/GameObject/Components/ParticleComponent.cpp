#include "PrecompiledHeaders.h"
#include "ParticleComponent.h"

std::string ParticleComponent::ComponentName() const 
{
	return "ParticleComponent";
}


//Constructor
ParticleComponent::ParticleComponent() :
	_fileName{},
	_shader{},
	_ParticleSystemUId{0}
{
}

ParticleComponent::~ParticleComponent()
{
}