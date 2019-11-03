#include "PrecompiledHeaders.h"
#include "AiComponent.h"



AiComponent::AiComponent(GameObject* parent, size_t uId, IComponentSystem* component)
	:IComponentSystem(parent, uId)
{
	if (component)
	{
		_destination = dynamic_cast<AiComponent*>(component)->_destination;
		for (auto& node : dynamic_cast<AiComponent*>(component)->GetPath())
			_path.emplace_back(new Node(*node));
	}
}

AiComponent::AiComponent(size_t id)
{

}

std::string AiComponent::ComponentName() const
{
	return "Ai Component";
}


void AiComponent::SerialiseComponent(Serialiser& document)
{

}

void AiComponent::Inspect()
{
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


void AiComponent::Move()
{
	// get next node
	// use script_move to move toward
	;
}