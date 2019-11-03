#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

Turret::Turret()
//:IComponentSystem(parent, uId)
{
	_attackRange = (float)EngineSystems::GetInstance()._aiSystem->GetMapTileSize();
	_attackRange *= 2; // 2 tileSize
	_attackRange *= _attackRange; // pow(2)
	_target = nullptr;
	_init = false;
	_state = (unsigned)AiState::IDLE;
	_health = 0;
}

void Turret::Init()
{
	std::unordered_map<size_t, GameObject*> temp = EngineSystems::GetInstance()._gameObjectFactory->getObjectlist();
	for (auto it : temp)
	{

		if (it.second->Get_uID() >= 1000 && it.second->GameObjectType() == (unsigned)TypeIdGO::PLAYER)
		{
			_target = it.second;
			break;
		}
	}
}
void Turret::Update(double dt)
{
	if (!_init)
	{
		Init();
		_init = true;
	}
	if (_health <= 0)
		DestoryThis();
	FSM();
}
void Turret::Exit()
{

}


Vector3& Turret::GetDestinationPos()
{
	return ((TransformComponent*)_target->GetComponent(ComponentId::TRANSFORM_COMPONENT))->GetPos();
}

Vector3& Turret::GetPosition()
{
	return ((TransformComponent*)this->GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT))->GetPos();
}

void Turret::FSM()
{
	if (!_target) // if no target
		_state = (unsigned)AiState::IDLE;

	// _destinationPos - currPos
	Vector3 tempVec3;// = GetDestinationPos() - GetPosition();
	// if (in range)
	if (tempVec3.SquaredLength() < _attackRange)
	{
		_state = (unsigned)AiState::ATTACKING;
		((GraphicComponent*)this->GetSibilingComponent((unsigned)ComponentId::GRAPHICS_COMPONENT))->SetTextureState(0);
	}
	else
	{
		_state = (unsigned)AiState::MOVING;
		((GraphicComponent*)this->GetSibilingComponent((unsigned)ComponentId::GRAPHICS_COMPONENT))->SetTextureState(1);
		Vector3 targetVec(
			(GetDestinationPos()._x - GetPosition()._x),
			(GetDestinationPos()._y - GetPosition()._y),
			0
		);
		Vector3 compareVec = { 0, 1, 0 };
		float dot = targetVec._x * compareVec._x + targetVec._y * compareVec._y;
		float det = targetVec._x * compareVec._y - targetVec._y * compareVec._x;
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate() = -atan2(det, dot);
	}

	switch (_state)
	{
	case (unsigned)AiState::IDLE:
		std::cout << "/t AI No Target!!!\n";
		break;
	case (unsigned)AiState::ATTACKING:
		std::cout << "/t AI ATK!!\n";
		break;
	default:
		break;
	}
}