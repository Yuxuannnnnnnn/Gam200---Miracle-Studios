#include "PrecompiledHeaders.h"
#include "LinkingFactory.h"

void LinkingFactory::SaveNewLinkID(int Id, size_t objectUId)
{
	_objectLinkMap.insert({ Id,objectUId });
}

GameObject* LinkingFactory::GetLinkIDObject(int Id)
{
	if (!Id)
		return nullptr;

	if (_objectLinkMap.find(Id) == _objectLinkMap.end())
		return nullptr;

	if(MyFactory.getObjectlist().find(_objectLinkMap[Id]) == MyFactory.getObjectlist().end())
		return nullptr;

	return MyFactory.getObjectlist()[_objectLinkMap[Id]];
}