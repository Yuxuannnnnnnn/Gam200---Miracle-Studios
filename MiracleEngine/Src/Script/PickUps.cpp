#include "PrecompiledHeaders.h"
#include "Script/PickUps.h"


PickUps::PickUps() : _lifeTime{ -666.f }, _pickupType{ (int)PickUp_Type::NONE }
{}

PickUps* PickUps::Clone()
{
	return new PickUps(*this);
}

void PickUps::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Lifetime") && document["Lifetime"].IsDouble())	//Checks if the variable exists in .Json file
	{
		_lifeTime = (document["Lifetime"].GetDouble());
	}
	if (document.HasMember("PickUps_Type") && document["PickUps_Type"].IsInt())	//Checks if the variable exists in .Json file
	{
		_pickupType = (document["PickUps_Type"].GetInt());
	}
}
//Function Not needed for scripts
void PickUps::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
}

void PickUps::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetString(rapidjson::StringRef(ToScriptName(_type)));
	prototypeDoc.AddMember("Script2Id", value, allocator);

	value.SetDouble(_lifeTime);
	prototypeDoc.AddMember("Lifetime", value, allocator);	
	
	value.SetInt(_pickupType);
	prototypeDoc.AddMember("PickUps_Type", value, allocator);
}

void PickUps::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	LogicComponent* protoLogicCom = dynamic_cast<LogicComponent*>(protoCom);

	size_t UId = protoLogicCom->GetScriptContianer()[_type];

	PickUps* script = (PickUps*)(MyLogicSystem.getScriptPtr(UId));

	if (!script)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}

	rapidjson::Value Lifetime;
	rapidjson::Value PickUps_Type;

	bool addComponentIntoSceneFile = false;

	if (script->_lifeTime != _lifeTime)
	{
		addComponentIntoSceneFile = true;
		Lifetime.SetDouble(_lifeTime);
	}	
	
	if (script->_pickupType != _pickupType)
	{
		addComponentIntoSceneFile = true;
		PickUps_Type.SetInt(_pickupType);
	}

	if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
	{
		rapidjson::Value scriptName;

		scriptName.SetString(rapidjson::StringRef(ToScriptName(_type)));
		value.AddMember("Script2Id", scriptName, allocator);


		if (!Lifetime.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("Lifetime", Lifetime, allocator);
		}

		if (!PickUps_Type.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("PickUps_Type", PickUps_Type, allocator);
		}
	}
}

void PickUps::Inspect()
{
	ImGui::Spacing();
	ImGui::InputDouble("Lifetime ", &_lifeTime);
	ImGui::Spacing();
	ImGui::InputInt("Pickup Type ", &_pickupType);
	ImGui::Spacing();
}

void PickUps::Update(double dt)
{
	if(dt < 0)
		return;

	if (_lifeTime != -666.f)
	{
		_lifeTime -= dt;

		if (_lifeTime < 0)
			GetParentPtr()->SetDestory();
	}
}
