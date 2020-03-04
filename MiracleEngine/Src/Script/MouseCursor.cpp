#include "PrecompiledHeaders.h"
#include "MouseCursor.h"

void MouseCursor::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("M.SpinSpeed") && document["M.SpinSpeed"].IsFloat())	//Checks if the variable exists in .Json file
		_spinSpeed = document["M.SpinSpeed"].GetFloat();

}
//Function not needed for scripts
void MouseCursor::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	//rapidjson::Value value;
	//
	//value.SetInt(_spinSpeed);
	//prototypeDoc.AddMember("M.SpinSpeed", value);

}

void MouseCursor::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetString(rapidjson::StringRef(ToScriptName(_type)));
	prototypeDoc.AddMember("Script2Id", value, allocator);

	value.SetFloat(_spinSpeed);
	prototypeDoc.AddMember("M.SpinSpeed", value, allocator);
}

void MouseCursor::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	LogicComponent* protoLogicCom = dynamic_cast<LogicComponent*>(protoCom);

	size_t UId = protoLogicCom->GetScriptContianer()[_type];

	MouseCursor* script = (MouseCursor*)(MyLogicSystem.getScriptPtr(UId));

	if (!script)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}

	rapidjson::Value SpinSpeed;

	bool addComponentIntoSceneFile = false;

	if (script->_spinSpeed != _spinSpeed)
	{
		addComponentIntoSceneFile = true;
		SpinSpeed.SetFloat(_spinSpeed);
	}

	if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
	{
		rapidjson::Value scriptName;

		scriptName.SetString(rapidjson::StringRef(ToScriptName(_type)));
		value.AddMember("Script2Id", scriptName, allocator);


		if (!SpinSpeed.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("M.SpinSpeed", SpinSpeed, allocator);
		}
	}
}

void MouseCursor::Inspect()
{
	ImGui::Spacing();
	ImGui::InputFloat("Spin Speed ", &_spinSpeed);
	ImGui::Spacing();
	ImGui::SliderFloat("Slider Spin Speed ", &_spinSpeed, 0.f , 5.f);
	ImGui::Spacing();
}

MouseCursor::MouseCursor() :
	_spinSpeed{0.f},
	_transform{ nullptr }
{
}

MouseCursor* MouseCursor::Clone()
{
	return new MouseCursor(*this);
}

void MouseCursor::Init()
{
	_transform = (TransformComponent*)GetParentPtr()->GetComponent(ComponentId::CT_Transform);
}

void MouseCursor::Update(double dt)
{
	_transform->SetPos(_input->GetMouseScreenPos());
	
	if (dt < 0)
		_transform->SetRotate(_transform->GetRotate() + 0.016 * _spinSpeed);
	else
		_transform->SetRotate(_transform->GetRotate() + dt * _spinSpeed);
}
