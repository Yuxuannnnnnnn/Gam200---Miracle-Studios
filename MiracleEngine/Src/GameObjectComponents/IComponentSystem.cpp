#include "PrecompiledHeaders.h"
#include "IComponentSystem.h"

std::string IComponentSystem::ComponentName() const
{
	std::cout << "IComponentSystem::ComponentName()" << std::endl;
	return "&";
}

size_t IComponentSystem::GetParentId() const
{
	return _ParentId;
}

//std::unordered_map < unsigned, IComponentSystem* >ChildGetCompList(GameObject* obj)
//{
//	return obj->GetComponentList();
//}

GameObject* IComponentSystem::GetParentPtr()
{
	return _ParentPtr;
}

IComponentSystem* IComponentSystem::GetSibilingComponent(unsigned _componentId)
{
	//_ParentPtr->GameObjectFactory::getRigidBodyComponent();

	//return ChildGetCompList(_ParentPtr)[_componentId];
	//ChildGetCompList(_ParentPtr)[_componentId];

	std::unordered_map < unsigned, IComponentSystem* > temp = _ParentPtr->GetComponentList();
	return temp[_componentId];

	// change above to just be
	//		return _ParentPtr->GetComponent(_componentId)
	// func below
	//		IComponentSystem* GameObject::GetComponent(TypeIdComponent typeId)
}
