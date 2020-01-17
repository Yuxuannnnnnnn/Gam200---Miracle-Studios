#pragma once
#include "GameObject/IComponent.h"
#include "GameObject/IAllocator.h"
#include "ParticleComponent.h"
#include "Tools/MathLib/Math.h"

class ParticleSystemComponent : public IComponent
{
public:
	size_t _startAmount;	// amount of particle to be create at the start of the system;
	size_t _limitAmount;	// amount of particle to be alive by this system
	size_t _releaseAmount;	// amount of particle can be by this system
	float _Lifetime;		// life time of the system 

	bool _loop;				// loop ingore _Lifetime and _releaseAmount

	bool _startCreation;

	//for graphic -> create particleComponent
	std::string _particleSprite;
	std::string _particleShader;
	//RenderLayer _renderlayer; // should be default

	//for transform -> create transformComponent
	Vec3 _particleOrigin;
	Vec3 _particleStartScale;
	Vec3 _particleGrowRate;
	Vec3 _particleLimitScale;
	float _particleRotation;

	//for physics -> create rigidbody2DComponent
	Vec3 _particleInitialVel;
	Vec3 _particleForce;
	Vec3 _particleAccel;

	// behaviour parttern -> most likely need a some api behaviour
	float _particleLifetime;

	std::vector<ParticleComponent*> _particleList; // store all the particle Component this system creates
public:

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{

		//ParticleComponent* protoParticleCom = dynamic_cast<ParticleComponent*>(protoCom);

		//bool addComponentIntoSceneFile = false;
		//rapidjson::Value fileName;
		//rapidjson::Value shader;

		//if (protoParticleCom->_fileName.compare(_fileName))	//If audiofile of Object is diff from prototype
		//{
		//	addComponentIntoSceneFile = true;
		//	fileName.SetString(rapidjson::StringRef(_fileName.c_str()));
		//}


		//if (protoParticleCom->_shader.compare(_shader))	//If audiofile of Object is diff from prototype
		//{
		//	addComponentIntoSceneFile = true;
		//	shader.SetString(rapidjson::StringRef(_shader.c_str()));
		//}


		//if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		//{
		//	value.AddMember("ParticleComponent", rapidjson::Value(true));

		//	if (!fileName.IsNull())
		//	{
		//		value.AddMember("ParticleFileName", fileName, allocator);
		//	}

		//	if (!shader.IsNull())
		//	{
		//		value.AddMember("ParticleShaderName", shader, allocator);
		//	}
		//}
	}


	virtual void Inspect() override;

	//Constructor
	ParticleSystemComponent();
	virtual ~ParticleSystemComponent();
	ParticleSystemComponent(const ParticleSystemComponent& rhs) = default;
	ParticleSystemComponent& operator=(const ParticleSystemComponent& rhs) = default;

	ParticleSystemComponent* CloneComponent() { return new ParticleSystemComponent(*this); }
};