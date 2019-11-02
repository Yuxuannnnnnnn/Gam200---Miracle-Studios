#include "PrecompiledHeaders.h"
#include "AiComponent.h"

AiComponent::AiComponent(size_t id)
{
	SetParentId(id);
}

std::string AiComponent::ComponentName() const
{
	return "Ai Component";
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
}
void AiComponent::Exit()
{

}

Vector3& AiComponent::GetDestinationPos()
{
	return _destinationPos;
}

Vector3& AiComponent::GetPosition()
{
	return ((TransformComponent*)this->GetSibilingComponent((unsigned)TypeIdComponent::TRANSFORMCOMPONENT))->GetPos();
}

std::vector<Node*>& AiComponent::GetPath()
{
	return _path;
}

void AiComponent::Move()
{
	// get next node
	// use script_move to move toward
	;
}
