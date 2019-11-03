#include "PrecompiledHeaders.h"
#include "Collider2D.h"



Collider2D::Collider2D(GameObject* parent, size_t uId, IComponentSystem * component)
	: IComponentSystem(parent, uId),
	_type{ unsigned(ColliderType::NONE_COLLIDER) },
	_layer{ 0 },
	_componentEnable{ true },
	_trigger{ true },
	_transform{ nullptr },
	_rigidbody{ nullptr }
{

	if (component)
	{
		Collider2D* collider2DComponent = dynamic_cast<Collider2D*>(component);
		 _type = collider2DComponent->_type;
		 _layer = collider2DComponent->_layer;
		 _componentEnable = collider2DComponent->_componentEnable;
		 _trigger = collider2DComponent->_trigger;
	}
}


std::string Collider2D::ComponentName() const
{
	return "ColliderComponent";
}

void Collider2D::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("ColliderTypeId") && document["ColliderTypeId"].IsInt())	//Checks if the variable exists in .Json file
		_type = document["ColliderTypeId"].GetUint();
}



void Collider2D::Inspect()
{
}
