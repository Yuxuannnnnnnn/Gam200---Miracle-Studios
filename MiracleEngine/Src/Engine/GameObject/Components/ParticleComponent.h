#pragma once
#include "GameObject/IComponent.h"
#include "GameObject/IAllocator.h"

class ParticleComponent : public IComponent
{
private:
	//for graphic
	std::string _fileName;
	std::string _shader;
	//RenderLayer _renderlayer; // should be default

	size_t _ParticleSystemUId;
public:

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, DeSerialiser& SceneFile) override;
	virtual void Inspect() override;

	//Constructor
	ParticleComponent();
	virtual ~ParticleComponent();
	ParticleComponent(const ParticleComponent& rhs);
	ParticleComponent& operator=(const ParticleComponent& rhs);
};

