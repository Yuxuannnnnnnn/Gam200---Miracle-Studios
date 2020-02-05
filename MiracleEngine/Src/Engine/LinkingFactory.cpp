#include "PrecompiledHeaders.h"
#include "LinkingFactory.h"

void LinkingFactory::SaveNewLinkID(int Id, size_t objectUId)
{
	_objectLinkMap.insert({ Id,objectUId });
}