#include "PrecompiledHeaders.h"
#include "IdentityComponent.h"





IdentityComponent::IdentityComponent(GameObject* parent, size_t uId, IComponent* component)
	: IComponent(parent, uId)/*, _typeId{ (unsigned)TypeIdGO::NONE }*/, _ObjectType{ "" }
{
	//if (component)
	//{
	//	IdentityComponent* Icom = dynamic_cast<IdentityComponent*>(component);
	//	_typeId = Icom->_typeId;
	//	_name = Icom->_name;
	//	_ObjectType = Icom->_ObjectType;
	//}
}

IdentityComponent::IdentityComponent(IdentityComponent* component)
{
	//_typeId = component->_typeId;
	_name = component->_name;
	_ObjectType = component->_ObjectType;
}


std::string IdentityComponent::ComponentName() const
{
	return std::string("Identity Component");
}



//unsigned IdentityComponent::GameObjectType() const
//{
//	return _typeId;
//}
