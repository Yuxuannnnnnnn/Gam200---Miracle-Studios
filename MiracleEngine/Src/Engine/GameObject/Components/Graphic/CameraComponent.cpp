#include "PrecompiledHeaders.h"
#include "CameraComponent.h"


CameraComponent::CameraComponent(GameObject* parent, size_t uId, IComponent* component)
	: IComponent(parent, uId),
	_isCurrentCamera{ false },
	_cameraZoom{1.f}
{
	if (component)
	{
		CameraComponent* cameraComponent = dynamic_cast<CameraComponent*>(component);

	}
}



std::string CameraComponent::ComponentName() const
{
	return std::string("Camera Component");
}


void CameraComponent::Inspect()
{
	IComponent::Inspect();

	ImGui::Spacing();
	bool temp = _isCurrentCamera;
	ImGui::Checkbox("MainCamera", &temp);
	ImGui::Spacing();
	SetMainCamera(temp);


	ImGui::Spacing();
	ImGui::SliderFloat("Camera Zoom", &_cameraZoom, 0.1, 15);
	ImGui::Spacing();
}

bool CameraComponent::isMainCamera() const
{
	return _isCurrentCamera;
}

void CameraComponent::SetMainCamera(bool main)
{
	if (this->GetParentId() == 0)
		return;

	if (main)
	{
		MyCameraSystem.SetMainCamera(this->GetParentId());
		_isCurrentCamera = true;
	}
	else
	{
		if (MyCameraSystem.GetMainCameraUId() != this->GetParentId())
			_isCurrentCamera = false;
	}
}

void CameraComponent::Panning(const Vector3& p1, const Vector3& p2, float a)
{
	if (a > 0.999f)
		a = 0.999f;
	Vector3 result = p1 * (1 - a) + p2 * a;
	auto b = (TransformComponent*)GetSibilingComponent(ComponentId::CT_Transform);
	b->SetPos(result);
}

//void CameraComponent::Panning(const Vector3& p1, const Vector3& p2, float a, float dt)
//{
//}

void CameraComponent::SmoothFollow(const Vector3& player, float damping)
{

	auto b = (TransformComponent*)GetSibilingComponent(ComponentId::CT_Transform);

	Vector3 pos = b->GetPos();
	Vector3 newPos = (player - pos) * damping;
	b->SetPos(newPos);
}

void CameraComponent::SmoothFollow(const Vector3& player, float dt, float damping)
{

	auto b = (TransformComponent*)GetSibilingComponent(ComponentId::CT_Transform);

	Vector3 pos = b->GetPos();
	Vector3 newPos = (player - pos) * damping * dt;
	b->SetPos(newPos);
}

void CameraComponent::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("CameraComponent") && document["CameraComponent"].IsBool())
		SetEnable(document["CameraComponent"].GetBool());

	if (document.HasMember("isCurrentCamera"))
	{
		_isCurrentCamera = document["isCurrentCamera"].GetBool();

		SetMainCamera(_isCurrentCamera);
	}

	if (document.HasMember("cameraZoom"))
	{
		_cameraZoom = document["cameraZoom"].GetFloat();
	}
}

void CameraComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetBool(GetEnable());
	prototypeDoc.AddMember("CameraComponent", value);

	value.SetBool(true);
	prototypeDoc.AddMember("isCurrentCamera", rapidjson::Value(true));

	value.SetFloat(_cameraZoom);
	prototypeDoc.AddMember("cameraZoom", value);
}


void CameraComponent::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetBool(GetEnable());
	prototypeDoc.AddMember("CameraComponent", value, allocator);

	value.SetBool(true);
	prototypeDoc.AddMember("isCurrentCamera", rapidjson::Value(true), allocator);

	value.SetFloat(_cameraZoom);
	prototypeDoc.AddMember("cameraZoom", value, allocator);
}


void CameraComponent::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	//value.AddMember("CameraComponent", rapidjson::Value(true), allocator);
	CameraComponent* protoTransformCom = dynamic_cast<CameraComponent*>(protoCom);

	if (!protoTransformCom)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}


	bool addComponentIntoSceneFile = false;

	rapidjson::Value enable;
	rapidjson::Value currentCamera;
	rapidjson::Value cameraZoom;

	if (protoTransformCom->GetEnable() != this->GetEnable())
	{
		addComponentIntoSceneFile = true;
		enable.SetBool(GetEnable());
	}

	if (protoTransformCom->_isCurrentCamera != _isCurrentCamera)
	{
		currentCamera.SetBool(_isCurrentCamera);
		addComponentIntoSceneFile = true;

	}

	if (protoTransformCom->_cameraZoom != _cameraZoom)
	{
		cameraZoom.SetFloat(_cameraZoom);
		addComponentIntoSceneFile = true;
	}


	if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
	{
		if (!enable.IsNull())
			value.AddMember("CameraComponent", enable, allocator);
		else
			value.AddMember("CameraComponent", protoTransformCom->GetEnable(), allocator);

		if (!currentCamera.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("Position", currentCamera, allocator);
		}

		if (!cameraZoom.IsNull())
		{
			value.AddMember("cameraZoom", cameraZoom, allocator);
		}
	}
}

void CameraComponent::Init()
{
	if (_isCurrentCamera && GetEnable())
		MyCameraSystem.SetMainCamera(GetParentId());
}