#include "PrecompiledHeaders.h"
#include "MouseCursor.h"

void MouseCursor::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("M.SpinSpeed") && document["M.SpinSpeed"].IsFloat())	//Checks if the variable exists in .Json file
		_spinSpeed = document["M.SpinSpeed"].GetFloat();

}

void MouseCursor::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetInt(_spinSpeed);
	prototypeDoc.AddMember("M.SpinSpeed", value);

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
