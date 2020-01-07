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
ParticleSystemComponent::ParticleSystemComponent(const ParticleSystemComponent& rhs) :
	_startAmount{ rhs._startAmount },
	_limitAmount{ rhs._limitAmount },
	_releaseAmount{ rhs._releaseAmount },
	_Lifetime{ rhs._Lifetime },
	_loop{ rhs._loop },
	_startCreation{ rhs._startCreation },
	_particleSprite{ rhs._particleSprite },
	_particleShader{ rhs._particleShader },
	_particleOrigin{ rhs._particleOrigin },
	_particleStartScale{ rhs._particleStartScale },
	_particleGrowRate{ rhs._particleGrowRate },
	_particleLimitScale{ rhs._particleLimitScale },
	_particleRotation{ rhs._particleRotation },
	_particleInitialVel{ rhs._particleInitialVel },
	_particleForce{ rhs._particleForce },
	_particleAccel{ rhs._particleAccel },
	_particleLifetime{ rhs._particleLifetime }
{

}
ParticleSystemComponent& ParticleSystemComponent::operator=(const ParticleSystemComponent& rhs)
{
	_startAmount= rhs._startAmount ;
	_limitAmount= rhs._limitAmount ;
	_releaseAmount= rhs._releaseAmount ;
	_Lifetime= rhs._Lifetime ;
	_loop= rhs._loop ;
	_startCreation= rhs._startCreation ;
	_particleSprite = rhs._particleSprite ;
	_particleShader= rhs._particleShader ;
	_particleOrigin= rhs._particleOrigin ;
	_particleStartScale= rhs._particleStartScale ;
	_particleGrowRate= rhs._particleGrowRate ;
	_particleLimitScale= rhs._particleLimitScale ;
	_particleRotation= rhs._particleRotation ;
	_particleInitialVel= rhs._particleInitialVel ;
	_particleForce= rhs._particleForce ;
	_particleAccel= rhs._particleAccel ;
	_particleLifetime = rhs._particleLifetime;

	return *this;
}