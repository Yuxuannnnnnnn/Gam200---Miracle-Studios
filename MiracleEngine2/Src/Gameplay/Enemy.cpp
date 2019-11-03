#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

Enemy::Enemy()
//:IComponentSystem(parent, uId)
{
	_attackRange = (float)EngineSystems::GetInstance()._aiSystem->GetMapTileSize();
	_attackRange *= 2; // 2 tileSize
	_attackRange *= _attackRange; // pow(2)
	_target = nullptr;
	_init = false;
	_state = (unsigned)AiState::MOVING;
	_health = 0;
}

void Enemy::Init()
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
void Enemy::Update(double dt)
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
void Enemy::Exit()
{

}

Vector3& Enemy::GetDestinationPos()
{
	_destinationPos = ((TransformComponent*)_target->GetComponent(ComponentId::TRANSFORM_COMPONENT))->GetPos();
	return _destinationPos;
}

Vector3& Enemy::GetPosition()
{
	return ((TransformComponent*)this->GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT))->GetPos();
}

std::vector<Node*>& Enemy::GetPath()
{
	return _path;
}

void Enemy::Move()
{ // move directly to Target.Pos
	const float spd = 4.f;
	Vector3 moveVec(
		(GetDestinationPos()._x - GetPosition()._x),
		(GetDestinationPos()._y - GetPosition()._y),
		0
	);
	moveVec.Normalize();
	moveVec* spd;
							//std::cout << moveVec._x << " " << moveVec._y << std::endl;
	Vector3 a = ((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos();
	a += moveVec;
	((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->SetPos(a);
}
void Enemy::MoveNode()
{ // move to NextNod
							//std::cout << _nextNode->GetNodeId() << std::endl << std::endl;
	float spd = 4.f;
	Vector3 moveVec(
		(_nextNode->GetPosition()._x - GetPosition()._x),
		(_nextNode->GetPosition()._y - GetPosition()._y),
		0
	);
	moveVec.Normalize();
	moveVec* spd;

	Vector3 a = ((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos();
	a += moveVec;
	((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->SetPos(a);
}

void Enemy::FSM()
{
	if (!_target) // if no target
		_state = (unsigned)AiState::IDLE;

	// _destinationPos - currPos
	Vector3 tempVec3 = GetDestinationPos() - GetPosition();
	// if (in range)
	if (tempVec3.SquaredLength() < _attackRange)
	{
		_state = (unsigned)AiState::ATTACKING;
		// set Anim state to EyeRed
		//((GraphicComponent*)this->GetSibilingComponent((unsigned)ComponentId::GRAPHICS_COMPONENT))->SetAnim();
	}
	else
	{
		_state = (unsigned)AiState::MOVING;
		// set Anim state to EyeWhite
		//((GraphicComponent*)this->GetSibilingComponent((unsigned)ComponentId::GRAPHICS_COMPONENT))->SetAnim();
	}

	switch (_state)
	{
	case (unsigned)AiState::IDLE:
		//std::cout << "/t AI No Target!!!\n";
		break;
	case (unsigned)AiState::MOVING:
		//std::cout << "/t AI Move!!!\n";
// get pathfinding
		_path = EngineSystems::GetInstance()._aiSystem->PathFinding(GetPosition(), GetDestinationPos());
		if (_path.empty())
			break;
		_nextNode = _path.front();
		MoveNode();
		//Move();
		break;
	case (unsigned)AiState::ATTACKING:
		//std::cout << "/t AI ATK!!\n";
		Move();
		break;
	default:
		break;
	}
}