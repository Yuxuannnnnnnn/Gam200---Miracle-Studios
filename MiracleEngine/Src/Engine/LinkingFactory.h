#pragma once
#include <unordered_map>
#include "GameObject/GameObject.h"

class LinkingFactory
{
	std::unordered_map<int, size_t> _objectLinkMap;
public:
	LinkingFactory() {}

	void SaveNewLinkID(int Id, size_t objectUId);

	
};