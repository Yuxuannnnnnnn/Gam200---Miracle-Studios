#include "PrecompiledHeaders.h"
#include "AiComponent.h"



AiComponent::AiComponent(GameObject* parent, size_t uId, IComponentSystem* component)
	:IComponentSystem(parent, uId), _nextNode{ nullptr }, _attackRange{ 1.0f }, _state{ 0 }, _target{ nullptr }
{
	if (component)
	{
		_destinationPos = dynamic_cast<AiComponent*>(component)->_destinationPos;
		for (auto& node : dynamic_cast<AiComponent*>(component)->GetPath())
			_path.emplace_back(new Node(*node));
	}
}


//AiComponent::AiComponent(GameObject* target, GameObject* parent, size_t uId, IComponentSystem* component)
	//:IComponentSystem(parent, uId)
//{
	//_attackRange = (float)EngineSystems::GetInstance()._aiSystem->GetMapTileSize();
	//_attackRange *= _attackRange; // shitty ^2 function
	//_target = target;
	//_state = (unsigned)AiState::MOVING;

	//if (component)
	//{
	//	_destinationPos = dynamic_cast<AiComponent*>(component)->_destinationPos;
	//	for (auto& node : dynamic_cast<AiComponent*>(component)->GetPath())
	//		_path.emplace_back(new Node(*node));
	//}
//}

std::string AiComponent::ComponentName() const
{
	return "Ai Component";
}


void AiComponent::SerialiseComponent(Serialiser& document)
{
}

void AiComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
}

void AiComponent::Inspect()
{
	IComponentSystem::Inspect();
}


void AiComponent::Init()
{

}
void AiComponent::AiComponent::Update()
{
	// if _target.pos() != _destination
		// call AISystem::PathFinding()
		// save new map
	// call Script_Move() for next Node in _path

	// update FSM
	FSM();
}
void AiComponent::Exit()
{

}

Vector3& AiComponent::GetDestinationPos()
{
	return ((TransformComponent*)_target->GetComponent(ComponentId::TRANSFORM_COMPONENT))->GetPos();
}

Vector3& AiComponent::GetPosition()
{
	return ((TransformComponent*)this->GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT))->GetPos();
}

std::vector<Node*>& AiComponent::GetPath()
{
	return _path;
}

void AiComponent::Move()
{
	// get next node
	// use script_move to move toward
	
}
void AiComponent::Move(Vector3 nextNodePos)
{
	// get next node
	// use script_move to move toward
	
}

void AiComponent::FSM()
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

	//switch (_state)
	//{
	//case (unsigned)AiState::IDLE:
	//	std::cout << "/t AI No Target!!!";
	//	break;
	//case (unsigned)AiState::MOVING:
	//	// get pathfinding
	//	_path = EngineSystems::GetInstance()._aiSystem->PathFinding();
	//	_nextNode = _path.front();
	//	Move(_nextNode->GetPosition());
	//	break;
	//case (unsigned)AiState::ATTACKING:
	//	Move();
	//	break;
	//default:
	//	break;
	//}
}
