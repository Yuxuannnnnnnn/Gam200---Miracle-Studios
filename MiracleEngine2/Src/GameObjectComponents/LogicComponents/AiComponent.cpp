#include "PrecompiledHeaders.h"
#include "AiComponent.h"

AiComponent::AiComponent(size_t id)
{

}

std::string AiComponent::ComponentName() const
{
	return "Ai Component";
}

void AiComponent::Init()
{

}
void AiComponent::AiComponent::Update(std::vector<Node>& tilemap)
{
	// call the pathfinding algorithm
		// AiSystem::PathFinding()
	// call Move();
}
void AiComponent::Exit()
{

}

Vector3& AiComponent::GetDestination()
{
	return _destination;
}

std::vector<Node*>& AiComponent::GetPath()
{
	return _path;
}

Vector3& AiComponent::GetPosition()
{
	TransformComponent* temp = (TransformComponent*)this->GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT);
	return temp->GetPos();
}
