#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

Enemy::Enemy()
//:IComponentSystem(parent, uId)
{
	_attackRange = (float)EngineSystems::GetInstance()._aiSystem->GetMapTileSize();
	_attackRange *= 3; // 2 tileSize
	_attackRange *= _attackRange; // pow(2)
	_target = nullptr;
	_state = (unsigned)AiState::MOVING;
	_health = 1;
	_nextNode = nullptr;
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
	if (_timer > 0)
	{
		_timer -= dt;
		
		switch (_state)
		{
		case (unsigned)AiState::IDLE:
			//std::cout << "/t AI No Target!!!\n";
			break;
		case (unsigned)AiState::MOVING:
			MoveNode();
			break;
		case (unsigned)AiState::ATTACKING:
			Move();
			break;
		default:
			break;
		}
	}
	else // run AI
	{
		FSM();
		_timer = _timeCooldown;
	}
	return;
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

	// rotate to face player
	Vector3 compareVec = { 0, 1, 0 };
	float dot = moveVec._x * compareVec._x + moveVec._y * compareVec._y;
	float det = moveVec._x * compareVec._y - moveVec._y * compareVec._x;
	((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate() = -atan2(det, dot);

	((RigidBody2D*)GetSibilingComponent((unsigned)ComponentId::RIGIDBODY_COMPONENT))->AddForwardForce(5000);

	//moveVec.Normalize();
	//moveVec.operator*(spd); // moveVec*(spd) && moveVec*speed giving warning
	//						//std::cout << moveVec._x << " " << moveVec._y << std::endl;
	//((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos() += moveVec;
}
void Enemy::MoveNode()
{ // move to NextNod
							//std::cout << _nextNode->GetNodeId() << std::endl << std::endl;

// TODO : Check if in range of nextNode, then pop front of list and assign nextNode;

	float spd = 4.f;
	Vector3 moveVec(
		(_nextNode->GetPosition()._x - GetPosition()._x),
		(_nextNode->GetPosition()._y - GetPosition()._y),
		0
	);

	// check if should get the nextNextNode
	unsigned mapTileSize = 100 * 100; // next time is get the map size from AiComponent or sth
	if (moveVec.SquaredLength() < (float)mapTileSize)
	{
		if (_path.size() > 1)
		{
			Node* nextNextNode = *(++(_path.begin())); // get node after
			if (nextNextNode)
			{
				moveVec = Vector3(
					(nextNextNode->GetPosition()._x - GetPosition()._x),
					(nextNextNode->GetPosition()._y - GetPosition()._y),
					0
				);
				_nextNode = nextNextNode;
				//_path = EngineSystems::GetInstance()._aiSystem->PathFinding(GetPosition(), GetDestinationPos());
			}
			else
				_state = (unsigned)AiState::ATTACKING;
		}
	}

	// rotate to face player
	Vector3 compareVec = { 0, 1, 0 };
	float dot = moveVec._x * compareVec._x + moveVec._y * compareVec._y;
	float det = moveVec._x * compareVec._y - moveVec._y * compareVec._x;
	((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate() = -atan2(det, dot);

	// move towards node
	moveVec.Normalize();
	moveVec* (spd);
	//std::cout << moveVec._x << " " << moveVec._y << std::endl;
	((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos() += moveVec;
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
		((GraphicComponent*)this->GetSibilingComponent((unsigned)ComponentId::GRAPHICS_COMPONENT))->SetTextureState(0);
	}
	else
	{
		_state = (unsigned)AiState::MOVING;
		// set Anim state to EyeWhite
		((GraphicComponent*)this->GetSibilingComponent((unsigned)ComponentId::GRAPHICS_COMPONENT))->SetTextureState(1);
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
		{
			_state = (unsigned)AiState::MOVING;
			break;
		}			
		_nextNode = _path.front();
		//MoveNode();
		break;
	case (unsigned)AiState::ATTACKING:
		//std::cout << "/t AI ATK!!\n";
		break;
	default:
		break;
	}
}

void Enemy::OnCollision2DTrigger(Collider2D* other)
{
	//if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::PLAYER || other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::TURRET)
	//{
	//	DestoryThis();
	//}
}