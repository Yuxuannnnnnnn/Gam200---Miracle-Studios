#ifndef _COllISION_TABLE_H
#define _COllISION_TABLE_H

#include <unordered_map>
#include <unordered_set>

#include "CollisionTagIDs.h"

class CollisionTable
{
	typedef std::unordered_map<ColliderTag, std::unordered_set<ColliderTag>> TABLE;
	typedef std::pair<ColliderTag, std::unordered_set<ColliderTag>> ROW;

	std::unordered_map<std::string, size_t> _tagList;

public:
	TABLE _table;

	bool CheckCollisionTable(ColliderTag first, ColliderTag second);

	std::unordered_map<std::string, size_t>& GetTagList();

	CollisionTable();
	~CollisionTable();
};

#endif
