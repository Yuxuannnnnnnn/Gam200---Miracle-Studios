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
	void SerialiseComponent(Serialiser& document) override
	{
		//if (document.HasMember("ParticleFileName") && document["ParticleFileName"].IsString())	//Checks if the variable exists in .Json file
		//{ 
		//	_fileName = document["ParticleFileName"].GetString();
		//}
		//
		//if (document.HasMember("ParticleShaderName") && document["ParticleShaderName"].IsString())	//Checks if the variable exists in .Json file
		//{
		//	_shader = document["ParticleShaderName"].GetString();
		//}
	
	}



	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		//rapidjson::Value value;
		//
		//value.SetString(rapidjson::StringRef(_fileName.c_str()));
		//prototypeDoc.AddMember("ParticleFileName", value);
		//
		////value.SetInt(_typeId);
		////prototypeDoc.AddMember("GameObjectType", value);
		//
		//value.SetString(rapidjson::StringRef(_shader.c_str()));
		//prototypeDoc.AddMember("ParticleShaderName", value);
	}


	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)


	virtual void Inspect() override
	{

	}

	//Constructor
	ParticleComponent();
	virtual ~ParticleComponent();
	ParticleComponent(const ParticleComponent& rhs);
	ParticleComponent& operator=(const ParticleComponent& rhs);
};

