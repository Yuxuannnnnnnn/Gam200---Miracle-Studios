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

ParticleComponent::ParticleComponent(const ParticleComponent& rhs) :
	_fileName{rhs._fileName},
	_shader{ rhs._shader },
	_ParticleSystemUId{rhs._ParticleSystemUId}
{
	

}

ParticleComponent& ParticleComponent::operator=(const ParticleComponent& rhs)
{
	_fileName =rhs._fileName;
	_shader = rhs._shader;
	_ParticleSystemUId = rhs._ParticleSystemUId;
}